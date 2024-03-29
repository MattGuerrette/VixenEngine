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
