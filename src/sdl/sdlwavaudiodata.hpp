/*
 * Copyright (c) 2015, Benny Bobaganoosh
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED ANDON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SDL_WAV_AUDIO_DATA_INCLUDED_HPP
#define SDL_WAV_AUDIO_DATA_INCLUDED_HPP

#include "../iaudiodata.hpp"
#include <SDL2/SDL.h>
#include <string>

class SDLWAVAudioData : public IAudioData
{
public:
	SDLWAVAudioData(const std::string& fileName, bool streamFromFile);
	virtual ~SDLWAVAudioData();

	virtual size_t GenerateSamples(float* stream, size_t streamLength, 
			size_t pos, const SampleInfo& info);
	virtual size_t GetAudioLength();
private:
	Uint8* m_pos;
	Uint8* m_start;
	Uint8* m_end;
	//Uint32 m_length;

	SDLWAVAudioData(SDLWAVAudioData& other) { (void)other; }
	void operator=(const SDLWAVAudioData& other) { (void)other;}
};

#endif
