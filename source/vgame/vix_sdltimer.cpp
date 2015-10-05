/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

#include <vix_sdltimer.h>

namespace Vixen {

	SDLTimer::SDLTimer()
	{
		m_startTime = 0;
		m_curTime = 0;
		m_prevTime = 0;
		m_fps = 0.0f;
	}

	void SDLTimer::Start()
	{
		m_startTime = SDL_GetTicks();
	}

	void SDLTimer::Tick()
	{
		/*cache current time in prev*/
		m_prevTime = m_curTime;

		m_curTime = SDL_GetTicks();

		/*calculate delta time*/
		m_deltaTime = (float)(m_curTime - m_prevTime) / 1000.0f;
	}

	void SDLTimer::CalculateFPS()
	{
		static int frameCnt = 0;

		if (m_startTime < (SDL_GetTicks() - 1000.0f))
		{
			m_startTime = SDL_GetTicks();
			m_fps = (float)frameCnt;

			frameCnt = 0;
		}

		++frameCnt;
	}

	float SDLTimer::DeltaTime()
	{
		return m_deltaTime;
	}

	float SDLTimer::FPS()
	{
		return m_fps;
	}

	float SDLTimer::TotalTime()
	{
		return m_curTime;
	}
}
