#ifndef VIX_POINTLIGHT_H
#define VIX_POINTLIGHT_H

#include <vix_platform.h>
#include <vix_vector3.h>
#include <vix_color.h>

namespace Vixen {

    struct Light
    {
        
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
		Color		color;
		float		diffuseIntensity;
	    Vector3     position;
        Attenuation attenuation;
    };

}

#endif
