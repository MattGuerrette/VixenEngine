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
