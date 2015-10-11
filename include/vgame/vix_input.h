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

#ifndef VIX_INPUT_H
#define VIX_INPUT_H

#include <vix_platform.h>


namespace Vixen {

    enum class IMBUTTON
    {
        LEFT,
        RIGHT,
        MIDDLE
    };

	enum IKEY
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SPACE,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		NUM1,
		NUM2,
		NUM3,
		NUM4,
		NUM5,
		NUM6,
		NUM7,
		NUM8,
		NUM9,
		NUM0,
	};

	class IKeyboardState;
    class IMouseState;

	class VIX_API Input
	{
	public:
		static bool KeyPress(IKEY key);
		static bool SingleKeyPress(IKEY key);
		static bool KeyRelease(IKEY key);
		static void SetKeyboardState(IKeyboardState* keyState);
        static void SetMouseState(IMouseState* mouseState);

        static int  MouseX();
        static int  MouseY();
		static int  MouseWheelX();
		static int  MouseWheelY();
        static int  DeltaX(int val);
        static int  DeltaY(int val);

        static bool ButtonRelease(IMBUTTON button);
        static bool ButtonPress(IMBUTTON button);
        static bool SingleButtonPress(IMBUTTON button);

	private:
		static IKeyboardState* s_keyState;
        static IMouseState*    s_mouseState;
	};

}

#endif
