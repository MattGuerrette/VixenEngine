#ifndef VIX_POINTLIGHT_H
#define VIX_POINTLIGHT_H

#include <vix_platform.h>
#include <vix_vector3.h>

namespace Vixen {

    struct Light
    {
        Color color;
        float diffuseIntensity;
    };
    
    struct Attenuation
    {
        float range;
        float constant;
        float linear;
        float quadratic;
    };

    struct PointLight : Light
    {
	    Vector3     position;
        Attenuation attenuation;
    };

}

#endif
