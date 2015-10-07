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

#include <vix_cameracomponent.h>

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

    bool CameraComponent::s_MainCameraExists = false;

    CameraComponent::CameraComponent()
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

    CameraComponent::~CameraComponent()
    {
        delete m_camera;
    }

    bool CameraComponent::IsMainCamera()
    {
        return m_isMainCamera;
    }

    ICamera3D* CameraComponent::GetCamera()
    {
        return m_camera;
    }

    void CameraComponent::SetPerspective(float aspect, float fov, float znear, float zfar)
    {
        if(m_camera)
            m_camera->VSetPerspective(aspect, fov, znear, zfar);
    }

    void CameraComponent::SetView(const Vector3& eye, const Vector3& target, const Vector3& up)
    {
        if(m_camera)
            m_camera->VSetView(eye, target, up);
    }

    void CameraComponent::VOnInit()
    {
		
    }

    void CameraComponent::VOnEnable()
    {
		if (m_camera)
		{
			m_camera->VSetView(m_parentTransform->GetWorldPosition(),
				m_parentTransform->GetWorldPosition() + m_parentTransform->GetForward(),
				m_parentTransform->GetUp());
			m_camera->VUpdate(0.0f);
		}
    }

    void CameraComponent::VUpdate(float dt)
    {

        if(m_camera)
        {
            m_camera->VSetView(	m_parentTransform->GetWorldPosition(),
                                  m_parentTransform->GetWorldPosition() + m_parentTransform->GetForward(),
                                  m_parentTransform->GetUp());

            //update camera
            m_camera->VUpdate(dt);
        }

    }

    void CameraComponent::VOnDisable()
    {

    }

    void CameraComponent::VOnDestroy()
    {

    }

    void CameraComponent::VBindParent(GameObject* parent)
    {
        m_parent = parent;
		m_parentTransform = parent->GetTransform();
    }


}
