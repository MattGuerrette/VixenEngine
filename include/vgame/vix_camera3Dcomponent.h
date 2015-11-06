/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

		Component::Type VGetType();

		void VSetType(Component::Type type);

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
