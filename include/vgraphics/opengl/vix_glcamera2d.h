/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIX_GLCAMERA2D_H
#define VIX_GLCAMERA2D_H

#include <vix_platform.h>
#include <vix_glm.h>

namespace Vixen {

	/*
	*	Camera2D class
	*
	*   Describes an ORTHOGRAPHIC 2D camera
	*/
	class VIX_API GLCamera2D
	{
	public:
		GLCamera2D(float L,
			       float R,
				   float T,
				   float B);

		/*return projection*/
		const Mat4&  Projection();

		/*return view*/
		const Mat4&  View();

		/*update bounds*/
		void SetBounds(float L,
					   float R,
					   float T,
					   float B);

	private:
		Mat4  m_projection;
		Mat4  m_view;
		float m_left;
		float m_right;
		float m_top;
		float m_bottom;
	};
}

#endif
