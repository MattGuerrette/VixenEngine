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
