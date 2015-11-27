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

#include <vix_glmathfunctions.h>

namespace Vixen {

    MATRIX GLMathFunctions::MatrixRotation(Vector3 rotation)
	{
		return	MatrixRotationX(rotation.x) *
				MatrixRotationY(rotation.y) *
				MatrixRotationZ(rotation.z);
	}

	MATRIX GLMathFunctions::MatrixRotationX(float rotX)
	{

		return glm::mat4();
	}

	MATRIX GLMathFunctions::MatrixRotationY(float rotY)
	{

        return glm::mat4();
	}

	MATRIX GLMathFunctions::MatrixRotationZ(float rotZ)
	{

        return glm::mat4();
	}

	MATRIX GLMathFunctions::MatrixTranslation(Vector3 position)
	{
        glm::mat4x4 m;

		return glm::translate(m, glm::vec3(position.x, position.y, position.z));
	}

	MATRIX GLMathFunctions::MatrixScaling(Vector3 _scale)
	{
        glm::mat4x4 m;

		return glm::scale(m, glm::vec3(_scale.x, _scale.y, _scale.z));
	}

	MATRIX GLMathFunctions::MatrixInverse(MATRIX matrix)
	{
		return glm::inverse(matrix);
	}

	Vector3 GLMathFunctions::TransformVector(Vector3 v, MATRIX matrix)
	{
		glm::vec4 _v = { v.x, v.y, v.z, 1.0f };

		_v = matrix * _v;

		return Vector3(_v.x, _v.y, _v.z);
	}

	Vector3 GLMathFunctions::TransformVectorRotationScale(Vector3 v, MATRIX matrix)
	{
        glm::vec4 _v = { v.x, v.y, v.z, 0.0f };

		_v = matrix * _v;

		return Vector3(_v.x, _v.y, _v.z);
	}

}
