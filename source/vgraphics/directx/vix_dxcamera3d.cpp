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
        
        m_d3dViewport.TopLeftX = v.x;
        m_d3dViewport.TopLeftY = v.y;
        m_d3dViewport.Width = v.width;
        m_d3dViewport.Height = v.height;
        m_d3dViewport.MinDepth = v.minDepth;
        m_d3dViewport.MaxDepth = v.maxDepth;
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
        VUpdateViewport(m_viewport);
        return m_d3dViewport;
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