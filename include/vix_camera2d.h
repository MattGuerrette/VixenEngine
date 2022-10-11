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

#ifndef VIX_CAMERA2D_H
#define VIX_CAMERA2D_H

#include "vix_platform.h"

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
