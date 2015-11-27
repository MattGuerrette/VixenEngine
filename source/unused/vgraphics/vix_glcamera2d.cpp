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

#include <vix_glcamera2d.h>

namespace Vixen {

	GLCamera2D::GLCamera2D(float L,
						   float R,
						   float T,
						   float B)
	{
		SetBounds(L, R, T, B);
	}

	void GLCamera2D::SetBounds(float L,
							   float R,
							   float T,
							   float B)
	{
		m_left = L;
		m_right = R;
		m_top = T;
		m_bottom = B;

		/*create projection*/
		m_projection = glm::ortho(m_left, m_right, m_bottom, m_top);
		/*create view*/
		m_view = glm::mat4(1.0f);
	}

	const Mat4 & GLCamera2D::Projection()
	{
		return m_projection;
	}

	const Mat4 & GLCamera2D::View()
	{
		return m_view;
	}



}
