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
#include <vix_color.h>

namespace Vixen {

    struct Light
    {
        
    };

    struct PointLight : Light
    {
		Color		color;
		float		range;
		float		constant;
		float		linear;
		float		quadratic;
    };

	struct SpotLight : Light
	{
		Color		color;
		float		range;
		float		angle;
		float		constant;
		float		linear;
		float		quadratic;
		Vector3		unused;
	};

}

#endif
