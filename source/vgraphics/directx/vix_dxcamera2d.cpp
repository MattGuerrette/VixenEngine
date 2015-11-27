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
