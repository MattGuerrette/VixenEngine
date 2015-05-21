/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

#ifndef VIX_SDLINPUT_H
#define VIX_SDLINPUT_H

#include <vix_platform.h>
#include <vix_input.h>
#ifdef VIX_SYS_WINDOWS
#include <SDL.h>
#elif defined(VIX_SYS_LINUX)
#include <SDL2/SDL.h>
#endif#include <SDL.h>
#include <map>

#define MOUSECS_BUTTONS 3
#define MOUSECS_LEFT	0
#define MOUSECS_MIDDLE  1
#define MOUSECS_RIGHT	2

namespace Vixen {

	struct MouseClickState
	{
		Uint8 clicks;
		Uint8 state;
	};

	class VIX_API SDLMouseState
	{
	public:
		SDLMouseState();

		/*GETTERS*/
		int  X();
		int  Y();
		int  DeltaX(int val);
		int  DeltaY(int val);

		bool ButtonRelease(int button);
		bool ButtonPress(int button);
		bool SingleButtonPress(int button);

		/*State Methods*/
		void MouseMove(int x, int y);
		void MouseEvent(SDL_MouseButtonEvent mbEvent);
		void UpdatePrev();
	private:
		int					m_x;
		int					m_y;
		int                 m_prevX;
		int                 m_prevY;
		MouseClickState		m_current[MOUSECS_BUTTONS];
		MouseClickState		m_prev[MOUSECS_BUTTONS];
	};

	class VIX_API SDLKeyboardState
	{
		typedef std::map<SDL_Scancode, bool> KeyState;

	public:
		SDLKeyboardState();

		void KeyDown(SDL_Scancode code);
		void KeyUp(SDL_Scancode code);
		void UpdatePrev();
		bool KeyPress(IKEY key);
		bool SingleKeyPress(IKEY key);
	private:
		KeyState  m_current;
		KeyState  m_previous;

		SDL_Scancode convertFromIKEY(IKEY key);
	};

}

#endif
