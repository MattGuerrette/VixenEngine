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
