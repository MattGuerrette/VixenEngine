/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

#include <vix_matrix.h>
#include <cassert>

namespace Vixen {

	const Matrix Matrix::Identity(1, 0, 0, 0,
								  0, 1, 0, 0,
								  0, 0, 1, 0,
		                          0, 0, 0, 1);

	float* Matrix::operator[] (size_t row)
	{
		assert(row < 4);

		return m[row];
	}

	const float* Matrix::operator[] (size_t row) const
	{
		assert(row < 4);

		return m[row];
	}

	void Matrix::initMatrix(float m11, float m12, float m13, float m14,
							float m21, float m22, float m23, float m24,
							float m31, float m32, float m33, float m34,
							float m41, float m42, float m43, float m44)
	{
		m[0][0] = m11;
		m[0][1] = m12;
		m[0][2] = m13;
		m[0][3] = m14;

		m[1][0] = m21;
		m[1][1] = m22;
		m[1][2] = m23;
		m[1][3] = m24;

		m[2][0] = m31;
		m[2][1] = m32;
		m[2][2] = m33;
		m[2][3] = m34;

		m[3][0] = m41;
		m[3][1] = m42;
		m[3][2] = m43;
		m[3][3] = m44;
	}

	Vector3 Matrix::Left() const
	{
		Vector3 v;

		v.x = -m[0][0];
		v.y = -m[0][1];
		v.z = -m[0][2];

		return v;
	}

}
