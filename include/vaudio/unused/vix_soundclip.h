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

#ifndef VIX_SOUNDCLIP_H
#define VIX_SOUNDCLIP_H

#include <vix_platform.h>
#include <vix_fmod.h>

namespace Vixen {

	class VIX_API SoundClip
	{
	public:
		SoundClip(FMOD::System* system, const UString& path);

		~SoundClip();

	private:
		FMOD::Sound*  m_clip;
	};

}

#endif
