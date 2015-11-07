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

#ifndef VIX_SDLINPUT_H
#define VIX_SDLINPUT_H

#include <vix_platform.h>
#include <vix_input.h>
#include <vix_keyboardstate.h>
#include <vix_mousestate.h>

#ifdef VIX_SYS_WINDOWS
#include <SDL.h>
#elif defined(VIX_SYS_LINUX)
#include <SDL2/SDL.h>
#endif#include <SDL.h>
#include <map>

namespace Vixen {

	struct MouseClickState
	{
		Uint8 clicks;
		Uint8 state;
	};

	class VIX_API SDLMouseState : public IMouseState
	{
        static const int MOUSECS_BUTTONS = 3;
	public:
		SDLMouseState();

		/*GETTERS*/
		int  VMouseX();
		int  VMouseY();
		int  VMouseWheelX();
		int  VMouseWheelY();
		int  VDeltaX(int val);
		int  VDeltaY(int val);

		bool VButtonRelease(IMBUTTON button);
		bool VButtonPress(IMBUTTON button);
		bool VButtonPressSingle(IMBUTTON button);

		/*State Methods*/
		void MouseMove(int x, int y);
		void MouseEvent(SDL_MouseButtonEvent mbEvent);
		void MouseWheelEvent(SDL_MouseWheelEvent mwEvent);
		void UpdatePrev();
	private:
		int					m_x;
		int					m_y;
		int                 m_prevX;
		int                 m_prevY;
		int                 m_wx;
		int                 m_wy;
		int					m_prevWX;
		int					m_prevWY;
		MouseClickState		m_current[MOUSECS_BUTTONS];
		MouseClickState		m_prev[MOUSECS_BUTTONS];
	};

	class VIX_API SDLKeyboardState : public IKeyboardState
	{
		typedef std::map<SDL_Scancode, bool> KeyState;

	public:
		SDLKeyboardState();

		void KeyDown(SDL_Scancode code);
		void KeyUp(SDL_Scancode code);
		void UpdatePrev();

		bool VKeyPress(IKEY key);
		bool VSingleKeyPress(IKEY key);
		bool VKeyRelease(IKEY key);

	private:
		KeyState  m_current;
		KeyState  m_previous;

		SDL_Scancode convertFromIKEY(IKEY key);
	};

	class VIX_API SDLControllerState
	{
		typedef std::map<SDL_GameControllerButton, bool> ControllerState;
		typedef std::map<SDL_GameControllerAxis, Sint16> AxisState;
	public:
		SDLControllerState();

		void Axis(SDL_GameControllerAxis axis, Sint16 val, int controller);
		void ButtonDown(SDL_GameControllerButton button, int controller);
		void ButtonUp(SDL_GameControllerButton button, int controller);
		void UpdatePrev();

		float VAxis(IAXIS axis, int controller);
		bool VButtonPress(IBUTTON button, int controller);
		bool VButtonPressSingle(IBUTTON button, int controller);
		bool VButtonRelease(IBUTTON button, int controller);

	private:
		ControllerState m_currentControllers[4];
		ControllerState m_previousControllers[4];
		AxisState m_currentAxis[4];

		SDL_GameControllerButton convertFromIBUTTON(IBUTTON button);
		SDL_GameControllerAxis convertFromIAXIS(IAXIS axis);
	};

}

#endif
