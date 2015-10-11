/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
