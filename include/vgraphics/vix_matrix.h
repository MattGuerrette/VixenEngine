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

#ifndef VIX_MATRIX_H
#define VIX_MATRIX_H

#include <vix_platform.h>
#include <vix_math.h>
#include <vix_vector3.h>
#include <iostream>

namespace Vixen {

	/*
	*	4x4 Matrix class
	*/
	class VIX_API Matrix
	{
	public:
		float m[4][4];

	public:
		Matrix()
		{
			initMatrix(0, 0, 0, 0,
				       0, 0, 0, 0,
				       0, 0, 0, 0,
				       0, 0, 0, 0);
		}

		Matrix(float m11, float m12, float m13, float m14,
			   float m21, float m22, float m23, float m24,
			   float m31, float m32, float m33, float m34,
			   float m41, float m42, float m43, float m44)
		{
			initMatrix(m11, m12, m12, m14,
					   m21, m22, m23, m24,
				       m31, m32, m33, m34,
				       m41, m42, m43, m44);
		}

		Vector3 Left()		const;
		Vector3 Right()		const;
		Vector3 Forward()	const;
		Vector3 Backward()	const;
		Vector3 Up()		const;
		Vector3 Down()		const;


		//operator overloads
		float*			operator[] (size_t row);
		const float*	operator[] (size_t row) const;


		//static members
		static const Matrix Identity;

		UString ToString() const;

		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Matrix& m)
		{
			o << "Matrix\n"
				<< m.ToString();
			return o;
		}

	private:
		void initMatrix(float m11, float m12, float m13, float m14,
						float m21, float m22, float m23, float m24,
						float m31, float m32, float m33, float m34,
						float m41, float m42, float m43, float m44);
	};

	inline UString Matrix::ToString() const
	{
		USStream ss;
		ss  << std::fixed
			<< std::setprecision(3)
			<< "[ " << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]\n"
			<< "[ " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]\n"
			<< "[ " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]\n"
			<< "[ " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]\n";

		return ss.str();
	}
}

#endif
