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
