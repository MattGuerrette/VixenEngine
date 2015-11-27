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
