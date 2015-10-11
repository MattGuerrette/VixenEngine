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
