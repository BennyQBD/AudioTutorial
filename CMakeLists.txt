#Copyright (C) 2014 Barry Deeney
#Copyright (c) 2014, Benny Bobaganoosh
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:
#
#1. Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer. 
#2. Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

################
# CMAKE RULES! #
################
# Huge thanks to mxaddict for setting up the CMake build system!

# we need features that are 2.6 >= dependent
cmake_minimum_required(VERSION 2.6)

# lets name the project
project(AudioProject)

# add the -c and -Wall flags
add_definitions(
	-c
	-Wall
)

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
add_definitions( -O2 )
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS ${AudioProject_SOURCE_DIR}/src/*.h)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS
	${AudioProject_SOURCE_DIR}/src/*.cpp
	${AudioProject_SOURCE_DIR}/src/*.c
)

# Define the executable
add_executable(AudioProject ${HDRS} ${SRCS})

# We need a CMAKE_DIR with some code to find external dependencies
SET(AudioProject_CMAKE_DIR "${AudioProject_SOURCE_DIR}/cmake")

#######################################
# LOOK for the packages that we need! #
#######################################

# SDL2
INCLUDE(${AudioProject_CMAKE_DIR}/FindSDL2.cmake)

# Define the include DIRs
include_directories(
	${AudioProject_SOURCE_DIR}/headers
	${AudioProject_SOURCE_DIR}/sources
	${SDL2_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( AudioProject
	${SDL2_LIBRARIES}
)

