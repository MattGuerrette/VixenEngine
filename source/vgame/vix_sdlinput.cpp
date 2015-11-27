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

	bool SDLMouseState::VButtonPressSingle(IMBUTTON button)
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
        case Vixen::IKEY::ENTER:
            return SDL_SCANCODE_RETURN;
		default:
			return SDL_SCANCODE_0;
			break;
		}
	}


	/*************************CONTROLLER***********************/

	SDLControllerState::SDLControllerState()
	{
		for (int i = 0; i < 4; i++)
		{
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_DPAD_UP] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_DPAD_LEFT] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_DPAD_DOWN] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_A] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_B] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_X] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_Y] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_START] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_BACK] = false;
			m_currentControllers[i][SDL_CONTROLLER_BUTTON_INVALID] = false;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_LEFTX] = 0;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_LEFTY] = 0;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_RIGHTX] = 0;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_RIGHTY] = 0;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_TRIGGERLEFT] = 0;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_TRIGGERRIGHT] = 0;
			m_currentAxis[i][SDL_CONTROLLER_AXIS_INVALID] = 0;
		}
	}

	void SDLControllerState::Connected(bool status, int controller)
	{
		m_currentControllerStatus[controller] = status;
	}

	void SDLControllerState::Axis(SDL_GameControllerAxis axis, Sint16 val, int controller)
	{
		m_currentAxis[controller][axis] = val;
	}

	void SDLControllerState::ButtonDown(SDL_GameControllerButton button, int controller)
	{
		m_currentControllers[controller][button] = true;
	}

	void SDLControllerState::ButtonUp(SDL_GameControllerButton button, int controller)
	{
		m_currentControllers[controller][button] = false;
	}

	void SDLControllerState::UpdatePrev()
	{
		for (int i = 0; i < 4; i++)
		{
			m_previousControllers[i] = m_currentControllers[i];
		}
	}

	bool SDLControllerState::VConnected(int controller)
	{
		if (controller >= 4) return false;
		return m_currentControllerStatus[controller];
	}

	float SDLControllerState::VAxis(IAXIS axis, int controller)
	{
		if (controller >= 4) return 0;
		SDL_GameControllerAxis code = convertFromIAXIS(axis);
		return (float)m_currentAxis[controller][code] / (float)INT16_MAX;
	}

	bool SDLControllerState::VButtonPress(IBUTTON button, int controller)
	{
		if (controller >= 4) return false;
		SDL_GameControllerButton code = convertFromIBUTTON(button);
		return m_currentControllers[controller][code];
	}

	bool SDLControllerState::VButtonPressSingle(IBUTTON button, int controller)
	{
		if (controller >= 4) return false;
		SDL_GameControllerButton code = convertFromIBUTTON(button);
		return m_currentControllers[controller][code] && !m_previousControllers[controller][code];
	}

	bool SDLControllerState::VButtonRelease(IBUTTON button, int controller)
	{
		if (controller >= 4) return false;
		SDL_GameControllerButton code = convertFromIBUTTON(button);
		return !m_currentControllers[controller][code] && m_previousControllers[controller][code];
	}

	SDL_GameControllerButton SDLControllerState::convertFromIBUTTON(IBUTTON button)
	{
		switch (button)
		{
		case Vixen::IBUTTON::UP:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP;
		case Vixen::IBUTTON::LEFT:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT;
		case Vixen::IBUTTON::DOWN:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN;
		case Vixen::IBUTTON::RIGHT:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
		case Vixen::IBUTTON::A:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A;
		case Vixen::IBUTTON::B:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B;
		case Vixen::IBUTTON::X:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X;
		case Vixen::IBUTTON::Y:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y;
		case Vixen::IBUTTON::LEFTBUMPER:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
		case Vixen::IBUTTON::RIGHTBUMPER:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		case Vixen::IBUTTON::LEFTSTICK:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSTICK;
		case Vixen::IBUTTON::RIGHTSTICK:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK;
		case Vixen::IBUTTON::START:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_START;
		case Vixen::IBUTTON::BACK:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK;
		default:
			return SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID;
		}
	}

	SDL_GameControllerAxis SDLControllerState::convertFromIAXIS(IAXIS axis)
	{
		switch (axis)
		{
		case Vixen::IAXIS::LEFTX:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX;
		case Vixen::IAXIS::LEFTY:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY;
		case Vixen::IAXIS::RIGHTX:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX;
		case Vixen::IAXIS::RIGHTY:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY;
		case Vixen::IAXIS::LEFTTRIGGER:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT;
		case Vixen::IAXIS::RIGHTTRIGGER:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
		default:
			return SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID;
		}
	}
}
