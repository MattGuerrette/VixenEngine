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
        virtual bool VButtonPressSingle(IMBUTTON button) = 0;
    };

}

#endif
