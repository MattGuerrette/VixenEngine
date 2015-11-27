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

#ifndef VIX_UICOMPONENT_H
#define VIX_UICOMPONENT_H

#include <vix_platform.h>
#include <vix_camera2d.h>

namespace Vixen {

    class VIX_API IUIComponent
    {
    public:
        virtual ~IUIComponent() { };

        virtual void VRender(ICamera2D* camera) = 0;

    };

}

#endif
