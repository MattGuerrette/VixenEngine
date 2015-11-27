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

#ifndef VIX_CAMERA3D_H
#define VIX_CAMERA3D_H

#include <vix_platform.h>
#include <vix_vector3.h>

namespace Vixen {

	struct Viewport
	{
        float xPercent;
        float yPercent;
        float wPercent;
        float hPercent;
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;
        float sWidth;
        float sHeight;
	};

    class VIX_API ICamera3D
    {
    public:
        virtual ~ICamera3D() { }

		virtual Viewport VGetViewport() = 0;
		virtual void VSetViewport(Viewport v) = 0;
		virtual void VSetViewportVariables(float x, float y, float width, float height, float minDepth, float maxDepth) = 0;
		virtual void VSetFOV(float fov) = 0;
        virtual void VSetPerspective(float aspect, float fov, float znear, float zfar) = 0;
        virtual void VSetView(const Vector3& eye, const Vector3& target, const Vector3& up) = 0;
        virtual void VUpdateViewport(Viewport v) = 0;
        virtual void VUpdate() = 0;
    };

}

#endif
