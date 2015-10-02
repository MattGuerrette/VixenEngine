/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
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
