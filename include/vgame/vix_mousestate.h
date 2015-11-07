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
