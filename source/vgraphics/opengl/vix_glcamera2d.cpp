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
