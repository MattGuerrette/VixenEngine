#ifndef VIX_UICOMPONENT_H
#define VIX_UICOMPONENT_H

#include <vix_platform.h>
#include <vix_camera2d.h>

namespace Vixen {

    class VIX_API IUIComponent
    {
    public:
        virtual ~IUIComponent() { };

        virtual void VRender(ICamera2D* camera) = 0;
    };

}

#endif