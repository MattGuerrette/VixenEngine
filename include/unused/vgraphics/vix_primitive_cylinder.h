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
