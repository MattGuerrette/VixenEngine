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
