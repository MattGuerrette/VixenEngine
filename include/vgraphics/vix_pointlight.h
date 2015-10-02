#ifndef VIX_POINTLIGHT_H
#define VIX_POINTLIGHT_H

#include <vix_platform.h>
#include <vix_transform.h>

namespace Vixen {

    class VIX_API PointLight
    {
    public:
        PointLight();

        ~PointLight();

    private:
        Transform*  m_transform;
    };

}

#endif
