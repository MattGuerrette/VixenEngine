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

#ifndef VIX_MOUSESTATE_H
#define VIX_MOUSESTATE_H

#include <vix_platform.h>
#include <vix_input.h>

namespace Vixen {

    class VIX_API IMouseState
    {
    public:
        virtual ~IMouseState() { };

        virtual int  VMouseX() = 0;
        virtual int  VMouseY() = 0;
		virtual int  VMouseWheelX() = 0;
		virtual int  VMouseWheelY() = 0;
        virtual int  VDeltaX(int val) = 0;
        virtual int  VDeltaY(int val) = 0;

        virtual bool VButtonRelease(IMBUTTON button) = 0;
        virtual bool VButtonPress(IMBUTTON button) = 0;
        virtual bool VSingleButtonPress(IMBUTTON button) = 0;
    };

}

#endif