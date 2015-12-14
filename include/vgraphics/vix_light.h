#ifndef VIX_POINTLIGHT_H
#define VIX_POINTLIGHT_H

#include <vix_platform.h>
#include <vix_vector3.h>
#include <vix_color.h>

namespace Vixen {

    struct Light
    {
        
    };

    struct PointLight : Light
    {
		Color		color;
	    Vector3     position;
		float		range;
		float		constant;
		float		linear;
		float		quadratic;
		float		intensity;
    };

	struct SpotLight : Light
	{
		Color		color;
		Vector3     position;
		Vector3		forward;
		float		range;
		float		angle;
		float		constant;
		float		linear;
		float		quadratic;
		float		intensity;
	};

}

#endif
