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

#ifndef VIX_GLVERTEX_H
#define VIX_GLVERTEX_H

#include <vix_platform.h>
#include <vix_gl.h>


namespace Vixen {

	struct GLVertexPosColor
	{
		float x, y, z;
		float r, g, b, a;

		GLVertexPosColor() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
		}

		GLVertexPosColor(float _x, float _y, float _z,
						 float _r, float _g, float _b, float _a)
		{
			x = _x; y = _y; z = _z;
			r = _r; g = _g; b = _b; a = _a;
		}
	};

	struct GLVertexPosTex
	{
		float x, y, z;
		float u, v;

		GLVertexPosTex() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			u = 0.0f; v = 0.0f;
		}

		GLVertexPosTex(float _x, float _y, float _z,
					   float _u, float _v) {
			x = _x; y = _y; z = _z;
			u = _u; v = _v;
		}
	};

}

#endif
