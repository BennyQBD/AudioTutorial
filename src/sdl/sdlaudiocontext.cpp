#include "sdlaudiocontext.hpp"

static void SDLAudioContext_AudioCallback(void* userData, Uint8* streamIn, int length)
{
	SDLAudioContext* context = (SDLAudioContext*)userData;
	context->GenerateSamples(streamIn, length);
}

SDLAudioContext::SDLAudioContext()
{
	SDL_AudioSpec spec;

	// TODO: Don't hardcode these values!
	SDL_zero(spec);
	spec.freq = 44100;
	spec.format = AUDIO_S16SYS;
	spec.channels = 2;
	spec.samples = 2048;
	spec.callback = SDLAudioContext_AudioCallback;
	spec.userdata = this;

	// TODO: Handle different specs
	m_device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
	if(m_device == 0)
	{
		// TODO: Proper error handling
		throw SDL_GetError();
	}

	SDL_PauseAudioDevice(m_device, 0);
}

SDLAudioContext::~SDLAudioContext()
{
	SDL_CloseAudioDevice(m_device);
}

void SDLAudioContext::PlayAudio(AudioObject& ao)
{
	SDL_LockAudioDevice(m_device);

	// This prevents duplicates
	RemoveAudio(ao);
	m_playingAudio.push_back(&ao);

	SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::PauseAudio(AudioObject& ao)
{
	SDL_LockAudioDevice(m_device);

	RemoveAudio(ao);

	SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::StopAudio(AudioObject& ao)
{
	SDL_LockAudioDevice(m_device);

	if(RemoveAudio(ao))
	{
		ao.SetPos(0.0);
	}

	SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::GenerateSamples(Uint8* streamIn, int streamInLen)
{
	size_t streamLen = (size_t)(streamInLen/2);

	m_stream.reserve(streamLen);
	float* floatStream = *(float**)(&m_stream);

	for(size_t i = 0; i < streamLen; i++)
	{
		floatStream[i] = 0.0f;
	}

	std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
	std::vector<AudioObject*>::iterator end = m_playingAudio.end();
	for(; it != end; ++it)
	{
		if(!(*it)->GenerateSamples(floatStream, streamLen))
		{
			RemoveAudio(*(*it));
		}
	}

	Sint16* stream = (Sint16*)streamIn;
	for(size_t i = 0; i < streamLen; i++)
	{
		float val = floatStream[i];

		if(val > 1.0f)
		{
			val = 1.0f;
		}
		else if(val < -1.0f)
		{
			val = -1.0f;
		}

		stream[i] = (Sint16)(val * 32767);
	}
}

bool SDLAudioContext::RemoveAudio(AudioObject& ao)
{
	std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
	std::vector<AudioObject*>::iterator end = m_playingAudio.end();

	for(; it != end; ++it)
	{
		if(*it == &ao)
		{
			m_playingAudio.erase(it);
			return true;
		}
	}

	return false;
}

