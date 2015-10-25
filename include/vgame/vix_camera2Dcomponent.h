#ifndef VIX_CAMERA2DCOMPONENT_H
#define VIX_CAMERA2DCOMPONENT_H

#include <vix_platform.h>
#include <vix_component.h>
#include <vix_camera2d.h>

namespace Vixen {

    class VIX_API Camera2DComponent : public IComponent
    {
    public:
        Camera2DComponent();

        ~Camera2DComponent();

        void VOnInit();

        void VOnEnable();

        void VUpdate();

        void VOnDisable();

        void VOnDestroy();

        void VBindParent(GameObject* parent);

    private:
        ICamera2D*  m_camera;
    };
}

#endif
