#ifndef VIX_CAMERA2D_H
#define VIX_CAMERA2D_H

#include <vix_platform.h>

namespace Vixen {

    enum class OrthoType
    {
        ORTHO_LH,
        ORTHO_LH_OFFCENTER,
        ORTHO_RH,
        ORTHO_RH_OFFCENTER
    };

    struct OrthoRect
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    class VIX_API ICamera2D
    {
    public:
        virtual ~ICamera2D() { }

        virtual void VSetOrthoLHOffCenter(OrthoRect rect, float zNear, float zFar) = 0;
        virtual void VSetOrthoRHOffCenter(OrthoRect rect, float zNear, float zFar) = 0;
    };
}

#endif