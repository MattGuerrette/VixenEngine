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

#ifndef VIX_QUATERNION_H
#define VIX_QUATERNION_H

#include <vix_platform.h>
#include <vix_vector3.h>
#include <iostream>

namespace Vixen {

	class VIX_API Quaternion
	{
	public:
		float w;
		float x;
		float y;
		float z;

	public:
		inline Quaternion(float w, float x, float y, float z)
			: w(w), x(x), y(y), z(z)
		{

		}

		inline Quaternion(float scalar, const Vector3& vector)
		{
			w = scalar;
			x = vector.x;
			y = vector.y;
			z = vector.z;
		}

		//static functions
		static float Dot(const Quaternion& q, const Quaternion& r);

		//member functions
		float Dot(const Quaternion& q) const;
		float Norm() const;
		void  Normalize();
		float Length() const;
		Quaternion Inverse() const;
		Quaternion Unit() const;

		//operator overloads
		inline Quaternion& operator= (const Quaternion& rhs)
		{
			w = rhs.w;
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;

			return *this;
		}

		inline bool operator== (const Quaternion& rhs)
		{
			return	(w == rhs.w) &&
					(x == rhs.x) &&
					(y == rhs.y) &&
					(z == rhs.z);
		}

		inline bool operator!= (const Quaternion& rhs)
		{
			return !(*this == rhs);
		}

		float  operator[] (const size_t i) const;
		float& operator[] (const size_t i);
		Quaternion operator- (void) const;
		Quaternion operator+ (const Quaternion& rhs) const;
		Quaternion operator+ (float scalar) const;
		Quaternion operator- (const Quaternion& rhs) const;
		Quaternion operator- (float scalar) const;
		Quaternion operator* (const Quaternion& rhs) const;
		Quaternion operator* (float scalar) const;
		Quaternion& operator+= (float scalar);
		Quaternion& operator+= (const Quaternion& rhs);
		Quaternion& operator-= (float scalar);
		Quaternion& operator-= (const Quaternion& rhs);
		Quaternion& operator*= (float scalar);
		Quaternion& operator*= (const Quaternion& rhs);

		static const Quaternion Identity;
		static const Quaternion Zero;


		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Quaternion& q)
		{
			o << "Quaternion [ "
				<< "w:" << q.w << ", "
				<< "x:" << q.x << ", "
				<< "y:" << q.y << ", "
				<< "z:" << q.z << " ]";
			return o;
		}
	};

}

#endif
