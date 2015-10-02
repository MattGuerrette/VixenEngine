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