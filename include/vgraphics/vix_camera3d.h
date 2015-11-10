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
