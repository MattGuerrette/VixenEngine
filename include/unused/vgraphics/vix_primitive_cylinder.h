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

#ifndef VIX_PRIMITIVE_CYLINDER_H
#define VIX_PRIMITIVE_CYLINDER_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_vertex_defs.h>
#include <vix_color.h>
#include <vector>

namespace Vixen {

	class VIX_API PrimitiveCylinder
	{
	public:
		PrimitiveCylinder(void);
		PrimitiveCylinder(float radius, float height, size_t subdivisions, Color c);

		~PrimitiveCylinder();

		void RotateX(float dt);
		void RotateY(float dt);
		void RotateZ(float dt);

		void SetPosition(float x, float y, float z);
		void SetSubdivisions(size_t sub);

		size_t GetSubdivisions();
		size_t GetMaxSubdivisions();


		void Render(GLCamera3D* camera);

	private:
		Vec3                   m_position;
		GLShaderProgram*       m_program;
		VBuffers::PCVBuffer*   m_vBuffer;
		GLIndexBuffer*         m_iBuffer;
		float                  m_rotationX;
		float                  m_rotationY;
		float                  m_rotationZ;
		float                  m_radius;
		size_t                 m_subdivisions;
		float                  m_height;
		Color                  m_color;
		size_t                 m_vertCnt;
		std::vector<PositionColor> m_topVerts;
		std::vector<PositionColor> m_botVerts;
		std::vector<PositionColor> m_bodyVerts;

		/*UTILITY FUNCTIONS*/

		void init_shader_program();
		void init_color_vi_buffers();

		/*apply shader transform*/
		void applyTransform(GLCamera3D* camera);

		/*STATIC CONSTANTS*/

		static const size_t RINGS = 24;
		static const size_t SECTORS = 48;
		static const size_t SUBDIVISIONS = 12;
		static const size_t SPHERE_INDEX_COUNT = 60;
		static const size_t SPHERE_VERTEX_COUNT = 12;
	};


}


#endif
