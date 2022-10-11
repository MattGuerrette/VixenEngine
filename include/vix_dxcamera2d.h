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

#ifndef VIX_DXCAMERA2D_H
#define VIX_DXCAMERA2D_H

#include "vix_platform.h"
#include "vix_directx.h"
#include "vix_camera2d.h"

namespace Vixen {

    class VIX_API DXCamera2D : public ICamera2D
    {
    public:
        DXCamera2D();

        void VSetOrthoLHOffCenter(OrthoRect rect, float zNear, float zFar);
        void VSetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar);

        const DirectX::XMFLOAT4X4& Projection();

    private:
        OrthoType            m_type;
        DirectX::XMFLOAT4X4  m_projection;
        OrthoRect            m_rect;
        float                m_zNear;
        float                m_zFar;
    };

}

#endif
