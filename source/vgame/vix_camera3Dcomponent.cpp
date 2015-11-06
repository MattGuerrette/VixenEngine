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

#include <vix_camera3Dcomponent.h>

//NOTE:
//
//  Needs to eventually include, either OpenGL or DirectX
//  camera class, and switch based on renderer.
//  OpenGL impl. uses GLM
//  DirectX impl. uses DirectXMath
#ifdef VIX_SYS_WINDOWS
#include <vix_dxcamera3d.h>
#else
#include <vix_glcamera3d.h>
#endif

#include <vix_gameobject.h>
#include <vix_input.h>

namespace Vixen {

    bool Camera3DComponent::s_MainCameraExists = false;

    Camera3DComponent::Camera3DComponent() : Component(Type::UNUSED)
    {
        #ifdef VIX_SYS_WINDOWS
            m_camera = new DXCamera3D;
            m_camera->VSetPerspective(1280.0f / 720.0f, DirectX::XMConvertToRadians(45.0f), 0.01f, 1000.0f);
            if (!s_MainCameraExists)
            {
                s_MainCameraExists = true;
                m_isMainCamera = true;
            }
            else {
                m_isMainCamera = false;
            }
        #else
            m_camera = NULL;
        #endif
    }

    Camera3DComponent::~Camera3DComponent()
    {
        delete m_camera;
    }

    bool Camera3DComponent::IsMainCamera()
    {
        return m_isMainCamera;
    }

    ICamera3D* Camera3DComponent::GetCamera()
    {
        return m_camera;
    }

    void Camera3DComponent::SetPerspective(float aspect, float fov, float znear, float zfar)
    {
        if(m_camera)
            m_camera->VSetPerspective(aspect, fov, znear, zfar);
    }

    void Camera3DComponent::SetView(const Vector3& eye, const Vector3& target, const Vector3& up)
    {
        if(m_camera)
            m_camera->VSetView(eye, target, up);
    }

    void Camera3DComponent::VOnInit()
    {

    }

    void Camera3DComponent::VOnEnable()
    {
		if (m_camera)
		{
			m_camera->VSetView(m_parentTransform->GetWorldPosition(),
				m_parentTransform->GetWorldPosition() + m_parentTransform->GetForward(),
				m_parentTransform->GetUp());
			m_camera->VUpdate();
		}
    }

    void Camera3DComponent::VUpdate()
    {

        if(m_camera)
        {
            m_camera->VSetView(	m_parentTransform->GetWorldPosition(),
                                  m_parentTransform->GetWorldPosition() + m_parentTransform->GetForward(),
                                  m_parentTransform->GetUp());

            //update camera
            m_camera->VUpdate();
        }

    }

    void Camera3DComponent::VOnDisable()
    {

    }

    void Camera3DComponent::VOnDestroy()
    {

    }

    void Camera3DComponent::VBindParent(GameObject* parent)
    {
        m_parent = parent;
		m_parentTransform = parent->GetTransform();
    }

	void Camera3DComponent::VSetType(Component::Type type)
	{
		m_type = type;
	}

	Component::Type Camera3DComponent::VGetType()
	{
		return m_type;
	}

}
