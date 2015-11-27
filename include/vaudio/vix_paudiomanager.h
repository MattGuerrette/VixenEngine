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

#ifndef VIX_PAUDIOMANAGER_H
#define VIX_PAUDIOMANAGER_H

#include <vix_platform.h>
#include <vix_manager.h>
#include <vix_portaudio.h>
#include <vix_sndfile.h>

namespace Vixen {

	class VIX_API PAudioStream
	{
	public:
		PAudioStream();

		~PAudioStream();

	private:
		PaStream* m_stream;
	};

	class VIX_API PAudioManager
	{
		typedef std::vector<SNDFILE_DATA*> SoundList;
	public:
		PAudioManager(void);

		~PAudioManager(void);

		void Init();
		void Load(const UString& file);
		void Term();
		void Play(size_t index);
		void Stop();

	private:
		SoundList  m_sounds;
		PaStream*  m_stream;
	};

}

#endif
