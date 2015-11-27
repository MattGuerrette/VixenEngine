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
