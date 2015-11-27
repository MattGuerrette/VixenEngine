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

#include <vix_ray.h>

namespace Vixen {

	Ray::Ray(Vec3 start, Vec3 end)
	{
		m_start = start;
		m_end = end;
		m_direction = end - start;
		m_direction = glm::normalize(m_direction);
		m_vBuffer = new VBuffers::PCVBuffer(2);

		init_shader_program();
		init_color_vi_buffers();
	}

	Ray::~Ray()
	{
		delete m_program;
		delete m_vBuffer;
	}

	void Ray::SetStart(Vec3 start)
	{
		m_start = start;
		m_direction = m_end - start;
		m_direction = glm::normalize(m_direction);
		init_color_vi_buffers();
	}

	void Ray::SetEnd(Vec3 end)
	{
		m_end = end;
		m_direction = end - m_start;
		m_direction = glm::normalize(m_direction);
		init_color_vi_buffers();
	}

	void Ray::init_shader_program()
	{
		/*vertex shader info*/
		ShaderInfo vshader_info;
		vshader_info.filePath = VTEXT("Ray.vs");
		vshader_info.raw = VTEXT("");
		vshader_info.type = ShaderType::VERTEX_SHADER;

		/*fragment shader info*/
		ShaderInfo fshader_info;
		fshader_info.filePath = VTEXT("Ray.fs");
		fshader_info.raw = VTEXT("");
		fshader_info.type = ShaderType::FRAGMENT_SHADER;

		/*populate shader args*/
		ShaderArgs args;
		args[0] = vshader_info;
		args[1] = fshader_info;

		/*create shader program*/
		m_program = new GLShaderProgram(args);
	}

	void Ray::init_color_vi_buffers()
	{
		const std::array<PositionColor, 2> vTemp =
		{
			PositionColor(m_start.x, m_start.y, m_start.z,
			   Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			   PositionColor(m_direction.x * 50, m_direction.y * 50, m_direction.z * 50,
			   Colors::Blue.r, Colors::Blue.g, Colors::Blue.b, Colors::Blue.a),
		};
		m_vBuffer->set(0, 2, vTemp.data());
	}

	void Ray::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;
		GLuint colorLoc;

		m_program->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_VIEW, viewLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_WORLD, worldLoc);
		m_program->GetUniformLoc("gColor", colorLoc);

		Color m_color = Colors::LimeGreen;

		Mat4 world = Mat4(0.0f);
		world =
			glm::translate(Mat4(1.0f), m_start);

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		//glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
		glUniform4f(colorLoc, m_color.r, m_color.g, m_color.b, m_color.a);
	}

	void Ray::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		PositionColor::Enable(true);
		PositionColor::RenderArrays(2, GL_LINES);
		PositionColor::Enable(false);

		m_vBuffer->unbind();
		m_program->Unbind();
	}

	const Vec3& Ray::Start()
	{
		return m_start;
	}

	const Vec3& Ray::End()
	{
		return m_end;
	}

	const Vec3& Ray::Direction()
	{
		return m_direction;
	}
}
