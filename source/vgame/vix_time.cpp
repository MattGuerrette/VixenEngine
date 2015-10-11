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
