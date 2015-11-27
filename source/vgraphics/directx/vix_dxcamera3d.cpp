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

	void DXCamera3D::VSetViewport(Viewport v)
	{
        m_viewport = v;
	}

    void DXCamera3D::VUpdateViewport(Viewport v)
    {
        m_viewport = v;

    }

	void DXCamera3D::VSetViewportVariables(float x, float y, float width, float height, float minDepth, float maxDepth)
	{
		m_viewport.xPercent = x;
		m_viewport.yPercent = y;
		m_viewport.wPercent = width;
		m_viewport.hPercent = height;
		m_viewport.minDepth = minDepth;
		m_viewport.maxDepth = maxDepth;
        m_viewport.x = x * m_viewport.sWidth;
        m_viewport.y = y * m_viewport.sHeight;
        m_viewport.width = width * m_viewport.sWidth;
        m_viewport.height = height * m_viewport.sHeight;
	}

	void DXCamera3D::VSetFOV(float fov)
	{
		m_fov = fov;
        VSetPerspective(m_aspect, m_fov, m_znear, m_zfar);
	}

	D3D11_VIEWPORT DXCamera3D::GetViewport()
	{
        D3D11_VIEWPORT viewport;
        viewport.TopLeftX = m_viewport.x;
        viewport.TopLeftY = m_viewport.y;
        viewport.Width = m_viewport.width;
        viewport.Height = m_viewport.height;
        viewport.MinDepth = m_viewport.minDepth;
        viewport.MaxDepth = m_viewport.maxDepth;

        return viewport;
	}

	Viewport DXCamera3D::VGetViewport()
	{
		return m_viewport;
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
