/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIX_SDLTIMER_H
#define VIX_SDLTIMER_H

#include <vix_platform.h>
#ifdef VIX_SYS_WINDOWS
#include <SDL.h>
#elif defined(VIX_SYS_LINUX)
#include <SDL2/SDL.h>
#endif

#include <vix_singleton.h>

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
