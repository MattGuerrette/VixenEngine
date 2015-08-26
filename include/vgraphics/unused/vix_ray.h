#ifndef VIX_RAY_H
#define VIX_RAY_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_vertex_defs.h>
#include <vix_color.h>

namespace Vixen {

	class VIX_API Ray
	{
	public:
		Ray(Vec3 start, Vec3 end);

		~Ray();

		const Vec3& Start();
		const Vec3& End();
		const Vec3& Direction();

		void SetStart(Vec3 start);
		void SetEnd(Vec3 end);

		void Render(GLCamera3D* camera);

	private:
		Vec3  m_start;
		Vec3  m_end;
		Vec3  m_direction;
		GLShaderProgram*       m_program;
		VBuffers::PCVBuffer*   m_vBuffer;

	private:
		/*UTILITY FUNCTIONS*/

		void init_shader_program();
		void init_color_vi_buffers();

		/*apply shader transform*/
		void applyTransform(GLCamera3D* camera);
	};
}

#endif