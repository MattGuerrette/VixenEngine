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

#ifndef VIX_CAMERA2D_H
#define VIX_CAMERA2D_H

#include <vix_platform.h>

namespace Vixen {

    enum class OrthoType
    {
        ORTHO_LH,
        ORTHO_LH_OFFCENTER,
        ORTHO_RH,
        ORTHO_RH_OFFCENTER
    };

    struct OrthoRect
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    class VIX_API ICamera2D
    {
    public:
        virtual ~ICamera2D() { }

        virtual void VSetOrthoLHOffCenter(OrthoRect rect, float zNear, float zFar) = 0;
        virtual void VSetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar) = 0;
    };
}

#endif
