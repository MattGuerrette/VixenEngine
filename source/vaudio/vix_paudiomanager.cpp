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

#include <vix_paudiomanager.h>

namespace Vixen {

	PAudioStream::PAudioStream()
	{
		m_stream = NULL;
	}

	PAudioStream::~PAudioStream()
	{
		Pa_CloseStream(m_stream);
	}

	PAudioManager::PAudioManager()
	{
		m_stream = NULL;
	}

	PAudioManager::~PAudioManager()
	{

	}

	void PAudioManager::Init()
	{
		PAUDIO_Init();
	}

	void PAudioManager::Load(const UString& file)
	{
		std::string path = Vixen::UStringToStd(file);
		SNDFILE_DATA* data = SNDFILE_ReadFile(path.c_str());

		if(data) {
			m_sounds.push_back(data);
		}
	}

	void PAudioManager::Play(size_t index)
	{
		SNDFILE_DATA* data = m_sounds[index];
		if(m_stream)
			Pa_CloseStream(m_stream);

		PAUDIO_OpenDefaultStream(&m_stream, 0,  /* no input */
						data->sfinfo.channels,
						paFloat32,
						data->sfinfo.samplerate,
                        paFramesPerBufferUnspecified,
                        data);

		Pa_StartStream(m_stream);
	}

	void PAudioManager::Term()
	{
		PAUDIO_Term();
	}

}
