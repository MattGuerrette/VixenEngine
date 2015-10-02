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
