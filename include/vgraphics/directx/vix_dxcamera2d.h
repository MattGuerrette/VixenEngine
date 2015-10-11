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

#ifndef VIX_DXCAMERA2D_H
#define VIX_DXCAMERA2D_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_camera2d.h>

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
