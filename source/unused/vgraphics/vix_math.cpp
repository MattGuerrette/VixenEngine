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

#include <vix_math.h>

namespace Vixen {

	bool Math::IsNaN(float n)
	{
		return n != n;
	}

	bool Math::IsFinite(float n)
	{
		return false;
	}

	float Math::ToRadians(float angle)
	{
		const float rad_conv = PI / 180.0f;

		return rad_conv * angle;
	}

	float Math::ToDegrees(float angle)
	{
		const float deg_conv = 180.0f / PI;

		return deg_conv * angle;
	}

}
