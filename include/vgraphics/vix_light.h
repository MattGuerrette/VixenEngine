#ifndef VIX_POINTLIGHT_H
#define VIX_POINTLIGHT_H

#include <vix_platform.h>
#include <vix_vector3.h>

namespace Vixen {

    struct VIX_API ILight
    {
		Vector3 m_ambientColor;
    };

	struct VIX_API PointLight : ILight
	{
		Vector3 m_position;
		float m_radius;
	};

	struct VIX_API DirectionalLight : ILight
	{
		Vector3 m_direction;
	};
}

#endif
