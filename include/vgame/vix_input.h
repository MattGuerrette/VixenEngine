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
		ESC
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
