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

#include <vix_sdlinput.h>

#define MOUSECS_LEFT	0
#define MOUSECS_MIDDLE  1
#define MOUSECS_RIGHT	2

namespace Vixen {

	/*************************MOUSE**************************/

	SDLMouseState::SDLMouseState()
	{
		m_x = 0;
		m_y = 0;
		m_wx = 0;
		m_wy = 0;
		m_prevWX = 0;
		m_prevWY = 0;
		m_prevX = 0;
		m_prevY = 0;
		m_current[MOUSECS_LEFT].state = SDL_RELEASED;
		m_current[MOUSECS_RIGHT].state = SDL_RELEASED;
		m_current[MOUSECS_MIDDLE].state = SDL_RELEASED;
		m_prev[MOUSECS_LEFT].state = SDL_RELEASED;
		m_prev[MOUSECS_RIGHT].state = SDL_RELEASED;
		m_prev[MOUSECS_MIDDLE].state = SDL_RELEASED;

	}

	int SDLMouseState::VMouseX()
	{
		return m_x;
	}

	int SDLMouseState::VMouseY()
	{
		return m_y;
	}

	int SDLMouseState::VMouseWheelX()
	{
		if (m_wx != m_prevWX) {
			return m_wx - 50;
		}
		else {
			return 0;
		}
	}

	int SDLMouseState::VMouseWheelY()
	{
		
		return m_wy;
		
	}

	int SDLMouseState::VDeltaX(int val)
	{
		if(m_x != m_prevX) {
			return m_x - val;
		} else {
			return 0;
		}
	}

	int SDLMouseState::VDeltaY(int val)
	{
		if(m_y != m_prevY) {
			return m_y - val;
		} else {
			return 0;
		}
	}

	bool SDLMouseState::VButtonPress(IMBUTTON button)
	{
		if(button == IMBUTTON::LEFT)
            return m_current[MOUSECS_LEFT].state == SDL_PRESSED;
        else if(button == IMBUTTON::RIGHT)
            return m_current[MOUSECS_RIGHT].state == SDL_PRESSED;
        else
            return m_current[MOUSECS_MIDDLE].state == SDL_PRESSED;
	}

	bool SDLMouseState::VButtonRelease(IMBUTTON button)
	{
        if (button == IMBUTTON::LEFT)
            return m_current[MOUSECS_LEFT].state == SDL_RELEASED && m_prev[MOUSECS_LEFT].state == SDL_PRESSED;
        else if(button == IMBUTTON::RIGHT)
            return m_current[MOUSECS_RIGHT].state == SDL_RELEASED && m_prev[MOUSECS_RIGHT].state == SDL_PRESSED;
        else
            return m_current[MOUSECS_MIDDLE].state == SDL_RELEASED && m_prev[MOUSECS_MIDDLE].state == SDL_PRESSED;
	}

	bool SDLMouseState::VSingleButtonPress(IMBUTTON button)
	{
        if(button == IMBUTTON::LEFT)
            return m_current[MOUSECS_LEFT].state == SDL_PRESSED && m_prev[MOUSECS_LEFT].state == SDL_RELEASED;
        else if(button == IMBUTTON::RIGHT)
            return m_current[MOUSECS_RIGHT].state == SDL_PRESSED && m_prev[MOUSECS_RIGHT].state == SDL_RELEASED;
        else
            return m_current[MOUSECS_MIDDLE].state == SDL_PRESSED && m_prev[MOUSECS_MIDDLE].state == SDL_RELEASED;
	}

	void SDLMouseState::MouseMove(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	void SDLMouseState::MouseEvent(SDL_MouseButtonEvent mbEvent)
	{
		switch(mbEvent.button)
		{
		case SDL_BUTTON_LEFT:
			m_current[MOUSECS_LEFT].state = mbEvent.state;
			m_current[MOUSECS_LEFT].clicks = mbEvent.clicks;
			break;

		case SDL_BUTTON_RIGHT:
			m_current[MOUSECS_RIGHT].state = mbEvent.state;
			m_current[MOUSECS_RIGHT].clicks = mbEvent.clicks;
			break;

		case SDL_BUTTON_MIDDLE:
			m_current[MOUSECS_MIDDLE].state = mbEvent.state;
			m_current[MOUSECS_MIDDLE].clicks = mbEvent.clicks;
			break;
		}
	}

	void SDLMouseState::MouseWheelEvent(SDL_MouseWheelEvent mwEvent)
	{
		m_wx = mwEvent.x;
		m_wy = mwEvent.y;
	}

	void SDLMouseState::UpdatePrev()
	{
		m_prevWX = m_wx;
		m_prevWY = m_wy;
		m_prevX = m_x;
		m_prevY = m_y;
		m_wy = 0;
		memcpy(m_prev, m_current, sizeof(m_current));
	}

	/*************************KEYBOARD***********************/

	SDLKeyboardState::SDLKeyboardState()
	{

	}

	void SDLKeyboardState::KeyDown(SDL_Scancode code)
	{
		m_current[code] = true;
	}

	void SDLKeyboardState::KeyUp(SDL_Scancode code)
	{
		m_current[code] = false;
	}

	void SDLKeyboardState::UpdatePrev()
	{
		m_previous = m_current;
	}

	bool SDLKeyboardState::VKeyPress(IKEY key)
	{
		SDL_Scancode code = convertFromIKEY(key);
		return m_current[code];
	}

	bool SDLKeyboardState::VSingleKeyPress(IKEY key)
	{
		SDL_Scancode code = convertFromIKEY(key);
		return m_current[code] && !m_previous[code];
	}

	bool SDLKeyboardState::VKeyRelease(IKEY key)
	{
		SDL_Scancode code = convertFromIKEY(key);
		return !m_current[code] && m_previous[code];
	}

	SDL_Scancode SDLKeyboardState::convertFromIKEY(IKEY key)
	{
		switch (key)
		{
		case Vixen::IKEY::A:
			return SDL_SCANCODE_A;
		case Vixen::IKEY::B:
			return SDL_SCANCODE_B;
		case Vixen::IKEY::C:
			return SDL_SCANCODE_C;
		case Vixen::IKEY::D:
			return SDL_SCANCODE_D;
		case Vixen::IKEY::E:
			return SDL_SCANCODE_E;
		case Vixen::IKEY::F:
			return SDL_SCANCODE_F;
		case Vixen::IKEY::G:
			return SDL_SCANCODE_G;
		case Vixen::IKEY::H:
			return SDL_SCANCODE_H;
		case Vixen::IKEY::I:
			return SDL_SCANCODE_I;
		case Vixen::IKEY::J:
			return SDL_SCANCODE_J;
		case Vixen::IKEY::K:
			return SDL_SCANCODE_K;
		case Vixen::IKEY::L:
			return SDL_SCANCODE_L;
		case Vixen::IKEY::M:
			return SDL_SCANCODE_M;
		case Vixen::IKEY::N:
			return SDL_SCANCODE_N;
		case Vixen::IKEY::O:
			return SDL_SCANCODE_O;
		case Vixen::IKEY::P:
			return SDL_SCANCODE_P;
		case Vixen::IKEY::Q:
			return SDL_SCANCODE_Q;
		case Vixen::IKEY::R:
			return SDL_SCANCODE_R;
		case Vixen::IKEY::S:
			return SDL_SCANCODE_S;
		case Vixen::IKEY::T:
			return SDL_SCANCODE_T;
		case Vixen::IKEY::U:
			return SDL_SCANCODE_U;
		case Vixen::IKEY::V:
			return SDL_SCANCODE_V;
		case Vixen::IKEY::W:
			return SDL_SCANCODE_W;
		case Vixen::IKEY::X:
			return SDL_SCANCODE_X;
		case Vixen::IKEY::Y:
			return SDL_SCANCODE_Y;
		case Vixen::IKEY::Z:
			return SDL_SCANCODE_Z;
		case Vixen::IKEY::UP:
			return SDL_SCANCODE_UP;
		case Vixen::IKEY::DOWN:
			return SDL_SCANCODE_DOWN;
		case Vixen::IKEY::LEFT:
			return SDL_SCANCODE_LEFT;
		case Vixen::IKEY::RIGHT:
			return SDL_SCANCODE_RIGHT;
		case Vixen::IKEY::SPACE:
			return SDL_SCANCODE_SPACE;
		case Vixen::IKEY::F1:
			return SDL_SCANCODE_F1;
		case Vixen::IKEY::F2:
			return SDL_SCANCODE_F2;
		case Vixen::IKEY::F3:
			return SDL_SCANCODE_F3;
		case Vixen::IKEY::F4:
			return SDL_SCANCODE_F4;
		case Vixen::IKEY::F5:
			return SDL_SCANCODE_F5;
		case Vixen::IKEY::F6:
			return SDL_SCANCODE_F6;
		case Vixen::IKEY::F7:
			return SDL_SCANCODE_F7;
		case Vixen::IKEY::F8:
			return SDL_SCANCODE_F8;
		case Vixen::IKEY::F9:
			return SDL_SCANCODE_F9;
		case Vixen::IKEY::F10:
			return SDL_SCANCODE_F10;
		case Vixen::IKEY::F11:
			return SDL_SCANCODE_F11;
		case Vixen::IKEY::F12:
			return SDL_SCANCODE_F12;
		case Vixen::IKEY::NUM0:
			return SDL_SCANCODE_0;
		case Vixen::IKEY::NUM1:
			return SDL_SCANCODE_1;
		case Vixen::IKEY::NUM2:
			return SDL_SCANCODE_2;
		case Vixen::IKEY::NUM3:
			return SDL_SCANCODE_3;
		case Vixen::IKEY::NUM4:
			return SDL_SCANCODE_4;
		case Vixen::IKEY::NUM5:
			return SDL_SCANCODE_5;
		case Vixen::IKEY::NUM6:
			return SDL_SCANCODE_6;
		case Vixen::IKEY::NUM7:
			return SDL_SCANCODE_7;
		case Vixen::IKEY::NUM8:
			return SDL_SCANCODE_8;
		case Vixen::IKEY::NUM9:
			return SDL_SCANCODE_9;
		case Vixen::IKEY::ESC:
			return SDL_SCANCODE_ESCAPE;
		default:
			return SDL_SCANCODE_0;
			break;
		}
	}

}
