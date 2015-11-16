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

#include <vix_mathfunctions.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxmathfunctions.h>
#else
#include <vix_glmathfunctions.h>
#endif

namespace Vixen {


#ifdef VIX_SYS_WINDOWS
	MATROTATION MathFunctions::s_MatrixRotation = reinterpret_cast<MATROTATION>(DXMathFunctions::MatrixRotation);
	MATROTX     MathFunctions::s_MatrixRotationX = reinterpret_cast<MATROTX>(DXMathFunctions::MatrixRotationX);
	MATROTY     MathFunctions::s_MatrixRotationY = reinterpret_cast<MATROTY>(DXMathFunctions::MatrixRotationY);
	MATROTZ     MathFunctions::s_MatrixRotationZ = reinterpret_cast<MATROTZ>(DXMathFunctions::MatrixRotationZ);
	MATTRANSLATION MathFunctions::s_MatrixTranslation = reinterpret_cast<MATTRANSLATION>(DXMathFunctions::MatrixTranslation);
	MATSCALING	MathFunctions::s_MatrixScaling = reinterpret_cast<MATSCALING>(DXMathFunctions::MatrixScaling);
	MATINVERSE  MathFunctions::s_MatrixInverse = reinterpret_cast<MATINVERSE>(DXMathFunctions::MatrixInverse);
	VECTRANSFORMMATRIX MathFunctions::s_TransformVector = reinterpret_cast<VECTRANSFORMMATRIX>(DXMathFunctions::TransformVector);
	VECTRANSFORMMATRIXROTSCALE MathFunctions::s_TransformVectorRotationScale = reinterpret_cast<VECTRANSFORMMATRIXROTSCALE>(DXMathFunctions::TransformVectorRotationScale);
#else
MATROTATION MathFunctions::s_MatrixRotation = reinterpret_cast<MATROTATION>(GLMathFunctions::MatrixRotation);
MATROTX     MathFunctions::s_MatrixRotationX = reinterpret_cast<MATROTX>(GLMathFunctions::MatrixRotationX);
MATROTY     MathFunctions::s_MatrixRotationY = reinterpret_cast<MATROTY>(GLMathFunctions::MatrixRotationY);
MATROTZ     MathFunctions::s_MatrixRotationZ = reinterpret_cast<MATROTZ>(GLMathFunctions::MatrixRotationZ);
MATTRANSLATION MathFunctions::s_MatrixTranslation = reinterpret_cast<MATTRANSLATION>(GLMathFunctions::MatrixTranslation);
MATSCALING	MathFunctions::s_MatrixScaling = reinterpret_cast<MATSCALING>(GLMathFunctions::MatrixScaling);
MATINVERSE  MathFunctions::s_MatrixInverse = reinterpret_cast<MATINVERSE>(GLMathFunctions::MatrixInverse);
VECTRANSFORMMATRIX MathFunctions::s_TransformVector = reinterpret_cast<VECTRANSFORMMATRIX>(GLMathFunctions::TransformVector);
VECTRANSFORMMATRIXROTSCALE MathFunctions::s_TransformVectorRotationScale = reinterpret_cast<VECTRANSFORMMATRIXROTSCALE>(GLMathFunctions::TransformVectorRotationScale);
#endif

	MATRIX MathFunctions::MatrixRotation(Vector3 rotation)
	{
		return s_MatrixRotation(rotation);
	}

	MATRIX MathFunctions::MatrixRotationX(float rotX)
	{
		return s_MatrixRotationX(rotX);
	}

	MATRIX MathFunctions::MatrixRotationY(float rotY)
	{
		return s_MatrixRotationY(rotY);
	}

	MATRIX MathFunctions::MatrixRotationZ(float rotZ)
	{
		return s_MatrixRotationZ(rotZ);
	}

	MATRIX MathFunctions::MatrixScaling(Vector3 scale)
	{
		return s_MatrixScaling(scale);
	}

	MATRIX MathFunctions::MatrixTranslation(Vector3 position)
	{
		return s_MatrixTranslation(position);
	}

	MATRIX MathFunctions::MatrixInverse(MATRIX matrix)
	{
		return s_MatrixInverse(matrix);
	}

	Vector3 MathFunctions::TransformVector(Vector3 v, MATRIX matrix)
	{
		return s_TransformVector(v, matrix);
	}

	Vector3 MathFunctions::TransformVectorRotationScale(Vector3 v, MATRIX matrix)
	{
		return s_TransformVectorRotationScale(v, matrix);
	}

}
