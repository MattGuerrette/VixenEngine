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

#ifndef VIX_DXCAMERA3D_H
#define VIX_DXCAMERA3D_H

#include "vix_platform.h"
#include "vix_directx.h"
#include "vix_camera3d.h"

namespace Vixen {

    class VIX_API DXCamera3D : public ICamera3D
    {
    public:
        DXCamera3D();

		void VSetViewport(Viewport v);
		void VSetViewportVariables(float x, float y, float width, float height, float minDepth, float maxDepth);
		void VSetFOV(float fov);
        void VSetPerspective(float aspect, float fov, float znear, float zfar);
        void VSetView(const Vector3& eye, const Vector3& target, const Vector3& up);
        void VUpdate();

        DirectX::XMFLOAT4X4 Projection();
        DirectX::XMFLOAT4X4 View();
		DirectX::XMFLOAT4X4 InvViewProj();

		D3D11_VIEWPORT GetViewport();

        void     VUpdateViewport(Viewport v);

		Viewport VGetViewport();

    private:
        //DIRECTX MATH
        DirectX::XMFLOAT4X4 m_projection;
        DirectX::XMFLOAT4X4 m_view;

        DirectX::XMFLOAT3   m_position;
        DirectX::XMFLOAT3   m_look;
        DirectX::XMFLOAT3   m_right;
        DirectX::XMFLOAT3   m_up;

        Viewport            m_viewport;

        D3D11_VIEWPORT      m_d3dViewport;

        float               m_aspect;
        float               m_znear;
        float               m_zfar;
        float               m_fov;
    };

}

#endif
