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


#include <vix_dxcamera3d.h>

using namespace DirectX;

namespace Vixen {

    DXCamera3D::DXCamera3D()
    {
        m_aspect = 0.0f;
        m_fov = 0.0f;
        m_znear = 0.0f;
        m_zfar = 0.0f;
        m_right = XMFLOAT3(1.0f, 0.0f, 0.0f);

    }

    void DXCamera3D::VSetPerspective(float aspect, float fov, float znear, float zfar)
    {
        m_aspect = aspect;
        m_fov = fov;
        m_znear = znear;
        m_zfar = zfar;

        XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(fov,
            aspect, znear, zfar);
        XMStoreFloat4x4(&m_projection, XMMatrixTranspose(P));
    }

    void DXCamera3D::VSetView(const Vector3& eye, const Vector3& target, const Vector3& up)
    {
        m_position = XMFLOAT3(eye.x, eye.y, eye.z);
        m_look = XMFLOAT3(target.x, target.y, target.z);
        m_up = XMFLOAT3(up.x, up.y, up.z);

    }

    void DXCamera3D::VUpdate()
    {

		XMVECTOR eyePosition = XMLoadFloat3(&m_position);
		XMVECTOR focus = XMLoadFloat3(&m_look);
		XMVECTOR up = XMLoadFloat3(&m_up);

		XMMATRIX V = XMMatrixLookAtLH(eyePosition, focus, up);

        XMStoreFloat4x4(&m_view, XMMatrixTranspose(V));
    }

    XMFLOAT4X4 DXCamera3D::Projection()
    {
        return m_projection;
    }

    XMFLOAT4X4 DXCamera3D::View()
    {
        return m_view;
    }
}
