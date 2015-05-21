/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_audiomanager.h>

namespace Vixen {

	AudioManager::AudioManager()
	{
		
	}

	AudioManager::~AudioManager()
	{

	}


	FMOD::System* const AudioManager::System()
	{
		return m_system;
	}

	ErrCode AudioManager::VStartUp()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		DebugPrintF(VTEXT("AudioManager starting up..."));
		
		/*create fmod sound system*/
		error = FMOD_CheckError(FMOD::System_Create(&m_system));
		if (CheckError(error))
			return error;

		/*initialize fmod sound system*/
		error = FMOD_CheckError(m_system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, NULL));
		if (CheckError(error))
			return error;

		return error;
	}

	ErrCode AudioManager::VShutDown()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		DebugPrintF(VTEXT("AudioManager shutting down..."));

		/*close sound system*/
		error = FMOD_CheckError(m_system->close());
		/*release sound system*/
		error = FMOD_CheckError(m_system->release());

		return error;
	}

	void AudioManager::CreateSound(const UString& path)
	{
		m_sounds[path] = new SoundClip(m_system, path);
	}

}