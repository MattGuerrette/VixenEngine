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
