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

#include <vix_quaternion.h>
#include <cassert>
#include <math.h>

namespace Vixen {

	const Quaternion Quaternion::Identity(1, 0, 0, 0);
	const Quaternion Quaternion::Zero(0, 0, 0, 0);

	float Quaternion::Dot(const Quaternion& q) const
	{
		return	(w * q.w) +
				(x * q.x) +
				(y * q.y) +
				(z * q.z);
	}

	float Quaternion::Dot(const Quaternion& q, const Quaternion& r)
	{
		return	(q.w * r.w) +
				(q.x * r.x) +
				(q.y * r.y) +
				(q.z * r.z);
	}

	float Quaternion::Norm() const
	{
		float _w = w * w;
		float _x = x * x;
		float _y = y * y;
		float _z = z * z;

		return sqrt(_w + _x + _y + _z);
	}

	void Quaternion::Normalize()
	{
		float len = Length();
		assert(len != 0);

		(*this) *= 1.0f / len;
	}

	float Quaternion::Length() const
	{
		return sqrt(Norm());
	}

	Quaternion Quaternion::Unit() const
	{
		//Original implementation
		float norm = Norm();
		assert(norm != 0.0f);

		float invNorm = 1.0f / norm;
		float _w = w * invNorm;
		float _x = -x * invNorm; //negate vector part
		float _y = -y * invNorm; //negate vector part
		float _z = -z * invNorm; //negate vector part


		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::Inverse() const
	{
		float normSq = Norm() * Norm();
		float invNormSq = 1.0f / normSq;

		/*
		* Equivalent to:
		* Conjugate / Norm^2
		*/
		float _w = w * invNormSq;
		float _x = -x * invNormSq;
		float _y = -y * invNormSq;
		float _z = -z * invNormSq;

		return Quaternion(_w, _x, _y, _z);
	}

	float Quaternion::operator[] (const size_t i) const
	{
		assert(i < 4); //only 3 members

		return *(&x + i);
	}

	float& Quaternion::operator[] (const size_t i)
	{
		assert(i < 4); //only 3 members

		return *(&x + i);
	}

	Quaternion Quaternion::operator- (void) const
	{
		float _w = -w;
		float _x = -x;
		float _y = -y;
		float _z = -z;

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::operator+ (const Quaternion& rhs) const
	{
		float _w = w + rhs.w;
		float _x = x + rhs.x;
		float _y = y + rhs.y;
		float _z = z + rhs.z;

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::operator+ (float scalar) const
	{
		float _w = w + scalar;
		float _x = x + scalar;
		float _y = y + scalar;
		float _z = z + scalar;

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::operator- (const Quaternion& rhs) const
	{
		float _w = w - rhs.w;
		float _x = x - rhs.x;
		float _y = y - rhs.y;
		float _z = z - rhs.z;

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::operator- (float scalar) const
	{
		float _w = w - scalar;
		float _x = x - scalar;
		float _y = y - scalar;
		float _z = z - scalar;

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::operator* (float scalar) const
	{
		float _w = w * scalar;
		float _x = x * scalar;
		float _y = y * scalar;
		float _z = z * scalar;

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion Quaternion::operator* (const Quaternion& rhs) const
	{
		float _w = 0.0f;
		float _x = 0.0f;
		float _y = 0.0f;
		float _z = 0.0f;

		//calculate new w
		_w = (rhs.w * w) -
			(rhs.x * x) -
			(rhs.y * y) -
			(rhs.z * z);

		//calculate new x
		_x = (rhs.w * x) +
			(rhs.x * w) -
			(rhs.y * z) +
			(rhs.z * y);

		//calculate new y
		_y = (rhs.w * y) +
			(rhs.x * z) +
			(rhs.y * w) -
			(rhs.z * x);

		//calculate new z
		_z = (rhs.w * z) -
			(rhs.x * y) +
			(rhs.y * x) +
			(rhs.z * w);

		return Quaternion(_w, _x, _y, _z);
	}

	Quaternion& Quaternion::operator*= (const Quaternion& rhs)
	{
		*this = *this * rhs;

		return *this;
	}

	Quaternion& Quaternion::operator*= (float scalar)
	{
		*this = *this * scalar;

		return *this;
	}
}
