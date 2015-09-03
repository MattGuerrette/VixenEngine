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
