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
        void VUpdate(float dt);

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
