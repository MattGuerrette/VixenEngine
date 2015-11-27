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

#include <vix_time.h>

namespace Vixen {

	Time::Time()
	{
		m_startTime = 0;
		m_curTime = 0;
		m_prevTime = 0;
		m_fps = 0.0f;
	}

	void Time::Start()
	{
		Time::instance().m_startTime = SDL_GetTicks();
	}

	void Time::Tick()
	{
		/*cache current time in prev*/
		Time::instance().m_prevTime = Time::instance().m_curTime;

		Time::instance().m_curTime = SDL_GetTicks();

		/*calculate delta time*/
		Time::instance().m_deltaTime = (float)(Time::instance().m_curTime - Time::instance().m_prevTime) / 1000.0f;
	}

	void Time::CalculateFPS()
	{
		static int frameCnt = 0;

		if (Time::instance().m_startTime < (SDL_GetTicks() - 1000.0f))
		{
			Time::instance().m_startTime = SDL_GetTicks();
			Time::instance().m_fps = (float)frameCnt;

			frameCnt = 0;
		}

		++frameCnt;
	}

	float Time::DeltaTime()
	{
		return Time::instance().m_deltaTime;
	}

	float Time::FPS()
	{
		return Time::instance().m_fps;
	}

	float Time::TotalTime()
	{
		return Time::instance().m_curTime;
	}
}
