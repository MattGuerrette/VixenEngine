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

#include <vix_input.h>
#include <vix_keyboardstate.h>
#include <vix_mousestate.h>
#include <vix_sdlinput.h>

#ifdef VIX_SYS_LINUX
#include <cstddef>
#endif

#include <cstdint>

namespace Vixen {



	///////////////////////////////////////////
	// INPUT
	//////////////////////////////////////////

	IKeyboardState*			Input::s_keyState = NULL;
    IMouseState*			Input::s_mouseState = NULL;
	SDLControllerState*		Input::s_controllerState = NULL;

	bool Input::KeyPress(IKEY key)
	{
		return s_keyState->VKeyPress(key);
	}

	bool Input::KeyPressSingle(IKEY key)
	{
		return s_keyState->VSingleKeyPress(key);
	}

	bool Input::KeyRelease(IKEY key)
	{
		return s_keyState->VKeyRelease(key);
	}

	void Input::SetKeyboardState(IKeyboardState* keyState)
	{
		s_keyState = keyState;
	}


	/****************************************************MOUSE*************************************************/



    void Input::SetMouseState(IMouseState* mouseState)
    {
        s_mouseState = mouseState;
    }

    int Input::MouseX()
    {
        return s_mouseState->VMouseX();
    }

    int Input::MouseY()
    {
        return s_mouseState->VMouseY();
    }

	int Input::MouseWheelX()
	{
		return s_mouseState->VMouseWheelX();
	}

	int Input::MouseWheelY()
	{
		return s_mouseState->VMouseWheelY();
	}

    int Input::DeltaX(int val)
    {
        return s_mouseState->VDeltaX(val);
    }

    int Input::DeltaY(int val)
    {
        return s_mouseState->VDeltaY(val);
    }

    bool Input::MouseButtonPress(IMBUTTON button)
    {
        return s_mouseState->VButtonPress(button);
    }

    bool Input::MouseButtonRelease(IMBUTTON button)
    {
        return s_mouseState->VButtonRelease(button);
    }


	/****************************************************CONTROLLER*************************************************/


	void Input::SetControllerState(SDLControllerState * controllerState)
	{
		s_controllerState = controllerState;
	}

	bool Input::ControllerButtonPress(IBUTTON button, int controller)
	{
		return s_controllerState->VButtonPress(button, controller);
	}

	bool Input::ControllerButtonPressSingle(IBUTTON button, int controller)
	{
		return s_controllerState->VButtonPressSingle(button, controller);
	}

	bool Input::ControllerButtonRelease(IBUTTON button, int controller)
	{
		return s_controllerState->VButtonRelease(button, controller);
	}

	float Input::ControllerAxis(IAXIS axis, int controller)
	{
		return s_controllerState->VAxis(axis, controller);
	}

    bool Input::MouseButtonPressSingle(IMBUTTON button)
    {
        return s_mouseState->VButtonPressSingle(button);
    }

}
