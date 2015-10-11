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

#include <vix_dxcamera2d.h>

using namespace DirectX;

namespace Vixen {

    DXCamera2D::DXCamera2D()
    {
        XMStoreFloat4x4(&m_projection, XMMatrixTranspose(XMMatrixIdentity()));
    }


    void DXCamera2D::VSetOrthoLHOffCenter(OrthoRect rect, float zNear, float zFar)
    {
        m_rect = rect;
        XMMATRIX P = XMMatrixOrthographicOffCenterLH(rect.left, rect.right, rect.bottom, rect.top, zNear, zFar);
        XMStoreFloat4x4(&m_projection, XMMatrixTranspose(P));
    }



    void DXCamera2D::VSetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar)
    {
        m_rect = rect;

        XMMATRIX P = XMMatrixOrthographicOffCenterRH(rect.left, rect.right, rect.bottom, rect.top, zNear, zFar);
        XMStoreFloat4x4(&m_projection, XMMatrixTranspose(P));
    }

    const XMFLOAT4X4& DXCamera2D::Projection()
    {
        return m_projection;
    }

}
