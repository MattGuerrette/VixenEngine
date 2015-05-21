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

#ifndef VIX_PRIMITIVE_CUBE_H
#define VIX_PRIMITIVE_CUBE_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_primitive_cube.h>
#include <vix_vertex_defs.h>
#include <vix_color.h>

namespace Vixen {

	class VIX_API PrimitiveCube
	{
	public:
		PrimitiveCube();

		~PrimitiveCube();

		void RotateX(float dt);
		void RotateY(float dt);
		void RotateZ(float dt);

		void SetPosition(Vec3& position);
		void SetScale(Vec3& scale);
		void SetRotation(Vec3& rotation);
		void SetWorldMatrix(Mat4& matrix);
		void SetColor(const Color& color);

		void Render(GLCamera3D* camera);

	private:
		Vec3                   m_position;
		Vec3				   m_rotation;
		Vec3				   m_scale;
		Mat4                   m_world;
		bool                   m_usingCustomWorld;
		Color                  m_color;
		GLShaderProgram*       m_program;
		VBuffers::PCVBuffer*   m_vBuffer;
		GLIndexBuffer*         m_iBuffer;

		/*UTILITY FUNCTIONS*/

		void init_shader_program();
		void init_color_vi_buffers();

		/*apply shader transform*/
		void applyTransform(GLCamera3D* camera);

		/*STATIC CONSTANTS*/

		static const size_t COLOR_VERT_COUNT = 8;
		static const size_t COLOR_INDEX_COUNT = 24;
	};

}

#endif
