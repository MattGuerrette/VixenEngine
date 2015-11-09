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

#ifndef VIX_CAMERA3DCOMPONENT_H
#define VIX_CAMERA3DCOMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_camera3d.h>
#include <vix_transform.h>

namespace Vixen {

    class GameObject;

    class VIX_API Camera3DComponent : public Component
    {
        static bool s_MainCameraExists;
    public:
        Camera3DComponent();

        ~Camera3DComponent();

        void VOnInit();

        void VOnEnable();

        void VUpdate();

        void VOnDisable();

        void VOnDestroy();

        void VBindParent(GameObject* parent);

        void SetPerspective(float aspect, float fov, float znear, float zfar);

        void SetView(const Vector3& eye, const Vector3& target, const Vector3& up);
		
        ICamera3D* GetCamera();

        bool       IsMainCamera();

    private:
        GameObject*         m_parent;
		Transform*          m_parentTransform;
        bool                m_isMainCamera;
        ICamera3D*          m_camera;

		Component::Type    m_type;
    };

}

#endif