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

#ifndef VIX_DXCAMERA3D_H
#define VIX_DXCAMERA3D_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_camera3d.h>

namespace Vixen {

    class VIX_API DXCamera3D : public ICamera3D
    {
    public:
        DXCamera3D();

        void VSetPerspective(float aspect, float fov, float znear, float zfar);
        void VSetView(const Vector3& eye, const Vector3& target, const Vector3& up);
        void VUpdate();

        DirectX::XMFLOAT4X4 Projection();
        DirectX::XMFLOAT4X4 View();

    private:
        //DIRECTX MATH
        DirectX::XMFLOAT4X4 m_projection;
        DirectX::XMFLOAT4X4 m_view;

        DirectX::XMFLOAT3   m_position;
        DirectX::XMFLOAT3   m_look;
        DirectX::XMFLOAT3   m_right;
        DirectX::XMFLOAT3   m_up;

        float               m_aspect;
        float               m_znear;
        float               m_zfar;
        float               m_fov;
    };

}

#endif
