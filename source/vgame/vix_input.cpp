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

	IKeyboardState*			Input::s_keyState = nullptr;
    IMouseState*			Input::s_mouseState = nullptr;
	SDLControllerState*		Input::s_controllerState = nullptr;

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

	bool Input::ControllerConnected(int controller)
	{
		return s_controllerState->VConnected(controller);
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
