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

#ifndef VIX_TRANSFORM_H
#define VIX_TRANSFORM_H

#include <vix_platform.h>
#include <vix_math.h>
#include <vix_quaternion.h>
#include <vix_vector3.h>

namespace Vixen {

	class VIX_API Transform
	{
	protected:
		/*Rotation of transformation*/
		Quaternion  Rotation;

		/*Translation of transformation*/
		Vector3     Translation;

		/*3D scale of object (always applied in local space) as vector*/
		Vector3     Scale;

	public:
		inline Transform()
			:	Rotation(0, 0, 0, 0),
				Translation(0, 0, 0),
				Scale(1, 1, 1)
		{

		}

		/**
		* The identity transfor
		* (Rotation = Quaternion::Identity,
		*  Translation = Vector3::Zero,
		*  Scale = Vector3::One)
		*/
		static const Transform Identity;
	};

}

#endif
