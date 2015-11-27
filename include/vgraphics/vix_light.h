/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

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
