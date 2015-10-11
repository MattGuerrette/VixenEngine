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

#include <vix_mathfunctions.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxmathfunctions.h>
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
