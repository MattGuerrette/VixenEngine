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

#ifndef VIX_MATH_H
#define VIX_MATH_H

#include "vix_platform.h"
#include "vix_debugutil.h"

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
