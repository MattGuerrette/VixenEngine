/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

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
