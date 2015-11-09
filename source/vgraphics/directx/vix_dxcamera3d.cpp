/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
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

	void DXCamera3D::VSetViewport(Viewport v)
	{
        m_viewport = v;
	}

    void DXCamera3D::VUpdateViewport(Viewport v)
    {
        m_viewport = v;
        VSetPerspective(m_viewport.width / m_viewport.height, m_fov, m_znear, m_zfar);
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