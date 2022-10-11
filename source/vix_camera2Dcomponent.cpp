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

#include <vix_camera2Dcomponent.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxcamera2d.h>
#else
#include <vix_glcamera2d.h>
#endif

namespace Vixen {

    Camera2DComponent::Camera2DComponent() : Component(Type::CAMERA)
    {
        #ifdef VIX_SYS_WINDOWS
                m_camera = new DXCamera2D;


        #else
                m_camera = NULL;
        #endif
    }

    Camera2DComponent::~Camera2DComponent()
    {

    }

    void Camera2DComponent::VOnInit()
    {

    }

    void Camera2DComponent::VOnEnable()
    {

    }

    void Camera2DComponent::VUpdate()
    {

    }

    void Camera2DComponent::VOnDisable()
    {

    }

    void Camera2DComponent::VOnDestroy()
    {

    }

}
