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

#ifndef VIX_MATHFUNCTIONS_H
#define VIX_MATHFUNCTIONS_H

#include <vix_platform.h>
#include <vix_math.h>
#include <vix_vector3.h>

namespace Vixen {

	typedef MATRIX	(*MATROTATION)(Vector3);
	typedef MATRIX	(*MATSCALING)(Vector3);
	typedef MATRIX	(*MATTRANSLATION)(Vector3);
	typedef MATRIX	(*MATROTX)(float);
	typedef MATRIX	(*MATROTY)(float);
	typedef MATRIX	(*MATROTZ)(float);
	typedef MATRIX(*MATINVERSE)(MATRIX);

	typedef Vector3(*VECTRANSFORMMATRIX)(Vector3, MATRIX);
	typedef Vector3(*VECTRANSFORMMATRIXROTSCALE)(Vector3, MATRIX);

	class VIX_API MathFunctions
	{
	public:
		static MATRIX MatrixRotationX(float rotX);
		static MATRIX MatrixRotationY(float rotY);
		static MATRIX MatrixRotationZ(float rotZ);
		static MATRIX MatrixRotation(Vector3 rotation);
		static MATRIX MatrixScaling(Vector3 scale);
		static MATRIX MatrixTranslation(Vector3 position);
		static MATRIX MatrixInverse(MATRIX matrix);

		static Vector3 TransformVector(Vector3 v, MATRIX matrix);
		static Vector3 TransformVectorRotationScale(Vector3 v, MATRIX matrix);


		static MATROTATION		s_MatrixRotation;
		static MATROTX			s_MatrixRotationX;
		static MATROTY			s_MatrixRotationY;
		static MATROTZ			s_MatrixRotationZ;
		static MATTRANSLATION	s_MatrixTranslation;
		static MATSCALING		s_MatrixScaling;
		static MATINVERSE       s_MatrixInverse;

		static VECTRANSFORMMATRIX s_TransformVector;
		static VECTRANSFORMMATRIXROTSCALE s_TransformVectorRotationScale;
	};

}

#endif
