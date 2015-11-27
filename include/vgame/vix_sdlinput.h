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
#endif
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
		typedef std::map<SDL_GameControllerButton, bool> ControllerButtonState;
		typedef std::map<SDL_GameControllerAxis, Sint16> AxisState;
	public:
		SDLControllerState();

		void Connected(bool status, int controller);
		void Axis(SDL_GameControllerAxis axis, Sint16 val, int controller);
		void ButtonDown(SDL_GameControllerButton button, int controller);
		void ButtonUp(SDL_GameControllerButton button, int controller);
		void UpdatePrev();

		bool VConnected(int controller);
		float VAxis(IAXIS axis, int controller);
		bool VButtonPress(IBUTTON button, int controller);
		bool VButtonPressSingle(IBUTTON button, int controller);
		bool VButtonRelease(IBUTTON button, int controller);

	private:
		bool					m_currentControllerStatus[4];
		ControllerButtonState	m_currentControllers[4];
		ControllerButtonState	m_previousControllers[4];
		AxisState				m_currentAxis[4];

		SDL_GameControllerButton convertFromIBUTTON(IBUTTON button);
		SDL_GameControllerAxis convertFromIAXIS(IAXIS axis);
	};

}

#endif
