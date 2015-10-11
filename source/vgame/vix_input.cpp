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

#ifdef VIX_SYS_LINUX
#include <cstddef>
#endif

namespace Vixen {



	///////////////////////////////////////////
	// INPUT
	//////////////////////////////////////////

	IKeyboardState* Input::s_keyState = NULL;
    IMouseState*    Input::s_mouseState = NULL;

	bool Input::KeyPress(IKEY key)
	{
		return s_keyState->VKeyPress(key);
	}

	bool Input::SingleKeyPress(IKEY key)
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

    bool Input::ButtonPress(IMBUTTON button)
    {
        return s_mouseState->VButtonPress(button);
    }

    bool Input::ButtonRelease(IMBUTTON button)
    {
        return s_mouseState->VButtonRelease(button);
    }

    bool Input::SingleButtonPress(IMBUTTON button)
    {
        return s_mouseState->VSingleButtonPress(button);
    }

}
