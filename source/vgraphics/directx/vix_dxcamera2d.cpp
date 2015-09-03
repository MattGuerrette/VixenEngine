/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

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