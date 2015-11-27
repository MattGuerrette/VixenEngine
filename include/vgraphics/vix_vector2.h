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

#ifndef VIX_VECTOR2_H
#define VIX_VECTOR2_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_math.h>
#include <cassert>

namespace Vixen {

	class VIX_API Vector2
	{
	public:
		float x;
		float y;
	public:
		inline Vector2()
			: x(0), y(0)
		{

		}

		inline Vector2(float _x, float _y)
			: x(_x), y(_y)
		{

		}

		/*operators*/

		inline bool operator== (const Vector2& rhs)
		{
			return (x == rhs.x &&
				    y == rhs.y);
		}

		inline bool operator!= (const Vector2& rhs)
		{
			return !(*this == rhs);
		}

		inline Vector2 operator + (const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		inline Vector2 operator - (const Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		inline Vector2 operator * (const Vector2& rhs) const
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		inline Vector2 operator * (const float scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}

		inline Vector2 operator / (const Vector2& rhs) const
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		inline Vector2 operator / (const float scalar) const
		{
			assert(scalar != 0.0f); //cannot divide by zero!

			float invScalar = 1.0f / scalar;
			return Vector2(x * invScalar, y * invScalar);
		}

		inline Vector2& operator += (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		inline Vector2& operator += (const float scalar)
		{
			x += scalar;
			y += scalar;

			return *this;
		}

		inline Vector2& operator -= (const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		inline Vector2& operator -= (const float scalar)
		{
			x -= scalar;
			y -= scalar;

			return *this;
		}

		inline Vector2& operator *= (const Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;

			return *this;
		}

		inline Vector2& operator *= (const float scalar)
		{
			x *= scalar;
			y *= scalar;

			return *this;
		}

		inline Vector2& operator /= (const Vector2& rhs)
		{
			//probably should also assert here, but w.e
			x /= rhs.x;
			y /= rhs.y;

			return *this;
		}

		inline Vector2& operator /= (const float scalar)
		{
			assert(scalar != 0.0f);

			float invScalar = 1.0f / scalar;
			x *= invScalar;
			y *= invScalar;

			return *this;
		}

		inline float Length() const
		{
			return sqrt(x * x + y * y);
		}

		inline float LengthSquared() const
		{
			return x * x + y * y;
		}

		inline float Distance(const Vector2& other) const
		{
			return (*this - other).Length();
		}

		inline float Dot(const Vector2& other) const
		{
			return x * other.x + y * other.y;
		}

		inline float Angle(const Vector2& other) const
		{
			float angle = atan2(y, x) - atan2(other.y, other.x);

			return angle;
		}

		inline float normalise()
		{
			float len = Length();

			if(len > 0.0f)
			{
				float lenInv = 1.0f / len;
				x *= lenInv;
				y *= lenInv;
			}

			return len;
		}

		inline Vector2 Normalize() const
		{
			Vector2 ret = *this;
			ret.normalise();
			return ret;
		}

		UString ToString() const;

		inline VIX_API friend UOStream& operator <<
			(UOStream& o, const Vector2& v)
		{
			o << "Vector2 [ "
				<< v.ToString()
				<< " ]";
			return o;
		}


		//constants
		static const Vector2 Zero;
		static const Vector2 Unit;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
	};


	inline UString Vector2::ToString() const
	{
		USStream ss;
		ss <<  std::fixed
			<< std::setprecision(3)
			<< "X=" << x << " "
			<< "Y=" << y;

		return ss.str();
	}

}

#endif
