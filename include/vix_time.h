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

#ifndef VIX_SDLTIMER_H
#define VIX_SDLTIMER_H

#include "vix_platform.h"
#ifdef VIX_SYS_WINDOWS
#include <SDL.h>
#elif defined(VIX_SYS_LINUX)
#include <SDL2/SDL.h>
#endif

#include "vix_singleton.h"

namespace Vixen {

	class VIX_API Time : public Singleton<Time>
	{
	public:
		Time();

		/*start timer*/
		static void  Start();

		/*frame tick*/
		static void  Tick();

		/*time elapsed between frames*/
		static float DeltaTime();

		/*total elapsed runtime*/
		static float  TotalTime();

		/*frames per second*/
		static float FPS();

		/*calculate fps*/
		static void  CalculateFPS();


	private:
		Uint32  m_startTime;
		Uint32  m_curTime;
		Uint32  m_prevTime;
		float   m_fps;
		float   m_deltaTime;
	};

}

#endif
