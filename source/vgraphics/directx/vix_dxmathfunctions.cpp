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

#include <vix_dxmathfunctions.h>

using namespace DirectX;

namespace Vixen {

	MATRIX DXMathFunctions::MatrixRotation(Vector3 rotation)
	{
		return	MatrixRotationX(rotation.x) *
				MatrixRotationY(rotation.y) *
				MatrixRotationZ(rotation.z);
	}

	MATRIX DXMathFunctions::MatrixRotationX(float rotX)
	{
		return XMMatrixRotationX(XMConvertToRadians(rotX));
	}

	MATRIX DXMathFunctions::MatrixRotationY(float rotY)
	{
		return XMMatrixRotationY(XMConvertToRadians(rotY));
	}

	MATRIX DXMathFunctions::MatrixRotationZ(float rotZ)
	{
		return XMMatrixRotationZ(XMConvertToRadians(rotZ));
	}

	MATRIX DXMathFunctions::MatrixTranslation(Vector3 position)
	{
		return XMMatrixTranslation(position.x, position.y, position.z);
	}

	MATRIX DXMathFunctions::MatrixScaling(Vector3 scale)
	{
		return XMMatrixScaling(scale.x, scale.y, scale.z);
	}

	MATRIX DXMathFunctions::MatrixInverse(MATRIX matrix)
	{
		XMVECTOR determinant = XMMatrixDeterminant(matrix);

		return XMMatrixInverse(&determinant, matrix);
	}

	Vector3 DXMathFunctions::TransformVector(Vector3 v, MATRIX matrix)
	{
		XMFLOAT4 _v = { v.x, v.y, v.z, 1 };
		XMVECTOR _transformedVec = XMVector4Transform(XMLoadFloat4(&_v), matrix);

		XMStoreFloat4(&_v, _transformedVec);

		return Vector3(_v.x, _v.y, _v.z);
	}

	Vector3 DXMathFunctions::TransformVectorRotationScale(Vector3 v, MATRIX matrix)
	{
		XMFLOAT4 _v = { v.x, v.y, v.z, 0 };
		XMVECTOR _transformedVec = XMVector4Transform(XMLoadFloat4(&_v), matrix);

		XMStoreFloat4(&_v, _transformedVec);

		return Vector3(_v.x, _v.y, _v.z);
	}
}
