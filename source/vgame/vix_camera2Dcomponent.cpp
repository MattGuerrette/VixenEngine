#include <vix_camera2Dcomponent.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxcamera2d.h>
#else
#include <vix_glcamera2d.h>
#endif

namespace Vixen {

    Camera2DComponent::Camera2DComponent()
    {
        #ifdef VIX_SYS_WINDOWS
                m_camera = new DXCamera2D;
               
         
        #else
                m_camera = NULL;
        #endif
    }

    Camera2DComponent::~Camera2DComponent()
    {

    }

    void Camera2DComponent::VOnInit()
    {

    }

    void Camera2DComponent::VOnEnable()
    {

    }

    void Camera2DComponent::VUpdate()
    {

    }

    void Camera2DComponent::VOnDisable()
    {

    }

    void Camera2DComponent::VOnDestroy()
    {

    }

    void Camera2DComponent::VBindParent(GameObject* parent)
    {

    }

}