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

#ifndef VIX_CAMERA2DCOMPONENT_H
#define VIX_CAMERA2DCOMPONENT_H

#include "vix_platform.h"
#include "vix_component.h"
#include "vix_camera2d.h"

namespace Vixen {

    class VIX_API Camera2DComponent : public Component
    {
    public:
        Camera2DComponent();

        ~Camera2DComponent();

        void VOnInit();

        void VOnEnable();

        void VUpdate();

        void VOnDisable();

        void VOnDestroy();

    private:
        ICamera2D*  m_camera;
    };
}

#endif
