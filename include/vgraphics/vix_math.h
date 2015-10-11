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

#ifndef VIX_MATH_H
#define VIX_MATH_H

#include <vix_platform.h>
#include <vix_debugutil.h>

#include <cmath>

#ifdef VIX_SYS_WINDOWS
#include <DirectXMath.h>
#endif

#ifndef VIX_SYS_WINDOWS
#include <vix_glm.h>
#endif

namespace Vixen {

	const float PI = 3.141593f;
	const float HALF_PI = 1.5707965f;
	const float TWO_PI = 6.283186f;

	class VIX_API Math
	{
	public:

		static bool IsNaN(float n);
		static bool IsFinite(float n);
		static float ToRadians(float angle);
		static float ToDegrees(float angle);
	};


#ifdef VIX_SYS_WINDOWS
	typedef DirectX::XMMATRIX MATRIX;
#else
	typedef glm::mat4x4 MATRIX;
#endif
}


#endif
