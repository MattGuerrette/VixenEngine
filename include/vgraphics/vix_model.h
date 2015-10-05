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

#ifndef VIX_MODEL_H
#define VIX_MODEL_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_camera3d.h>
#include <vix_material.h>

namespace Vixen {

    class VIX_API IModel
    {
    public:
        virtual ~IModel() { }

        virtual bool VInitFromFile(File* file) = 0;
        virtual void VRender(float dt, float totalTime, ICamera3D* camera) = 0;
        virtual void VSetWorld(MATRIX* world) = 0;
        virtual void VSetMaterial(IMaterial* material) = 0;
        virtual void VBatchRender(MATRIX* world) = 0;

        virtual Vector3 VMin() = 0;
        virtual Vector3 VMax() = 0;
        virtual Vector3 VCenter() = 0;
        virtual Vector3 VSize() = 0;
    };

}

#endif
