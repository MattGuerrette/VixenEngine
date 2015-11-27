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

#include <vix_primitive_tube.h>
#include <vix_math.h>

namespace Vixen {

	PrimitiveTube::PrimitiveTube(float outRadius, float inRadius, float height, size_t subdivisions, Color c)
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VBuffers::PCVBuffer(32);
		m_iBuffer = new GLIndexBuffer(SPHERE_INDEX_COUNT);
		m_subdivisions = subdivisions;
		m_inRadius = inRadius;
		m_outRadius = outRadius;
		m_height = height;
		m_color = c;

		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveTube::~PrimitiveTube()
	{
		delete m_vBuffer;
		delete m_program;
		delete m_iBuffer;
	}

	void PrimitiveTube::SetSubdivisions(size_t sub)
	{
		m_subdivisions = sub;
		init_color_vi_buffers();
	}

	size_t PrimitiveTube::GetMaxSubdivisions()
	{
		return SUBDIVISIONS;
	}

	void PrimitiveTube::RotateX(float dt)
	{
		m_rotationX += dt * 50.0f;
	}

	void PrimitiveTube::RotateY(float dt)
	{
		m_rotationY += dt * 50.0f;
	}

	void PrimitiveTube::RotateZ(float dt)
	{
		m_rotationZ += dt * 50.0f;
	}

	void PrimitiveTube::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}

	size_t PrimitiveTube::GetSubdivisions()
	{
		return m_subdivisions;
	}


	void PrimitiveTube::init_color_vi_buffers()
	{
		m_topVerts.clear();
		m_botVerts.clear();
		m_inBodyVerts.clear();
		m_outBodyVerts.clear();

		const float ri = m_inRadius;
		const float ro = m_outRadius;
		const float h = 1.0f;
		const float min_sub = 3;
		const float max_sub = 12;
		const float a = TWO_PI / (m_subdivisions + (min_sub-1));

		////TOP CAP VERTS
		for(float i = 0; i <= TWO_PI; i += a)
		{
			m_topVerts.push_back(PositionColor(ri*cos(i), h, ri*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
			m_topVerts.push_back(PositionColor(ro*cos(i), h, ro*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
		}

		m_topVerts.push_back(PositionColor(ri, h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
		m_topVerts.push_back(PositionColor(ro, h, 0, 1.0f, 0.0f, 0.0f, 1.0f));



		//BOTTOM CAP VERTS
		for(float i = 0; i <= TWO_PI; i += a)
		{
			m_botVerts.push_back(PositionColor(ri*cos(i), -h, ri*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
			m_botVerts.push_back(PositionColor(ro*cos(i), -h, ro*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
		}

		m_botVerts.push_back(PositionColor(ri, -h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
		m_botVerts.push_back(PositionColor(ro, -h, 0, 1.0f, 0.0f, 0.0f, 1.0f));

		//MIDDLE
		for(float i = 0; i <= TWO_PI; i += a)
		{
			m_inBodyVerts.push_back(PositionColor(ri*cos(i), -h, ri*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
			m_inBodyVerts.push_back(PositionColor(ri*cos(i), h, ri*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
		}

		m_inBodyVerts.push_back(PositionColor(ri, -h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
		m_inBodyVerts.push_back(PositionColor(ri, h, 0, 1.0f, 0.0f, 0.0f, 1.0f));

		for(float i = 0; i <= TWO_PI; i += a)
		{
			m_outBodyVerts.push_back(PositionColor(ro*cos(i), -h, ro*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
			m_outBodyVerts.push_back(PositionColor(ro*cos(i), h, ro*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
		}

		m_outBodyVerts.push_back(PositionColor(ro, -h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
		m_outBodyVerts.push_back(PositionColor(ro, h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
	}

	void PrimitiveTube::init_shader_program()
	{
		/*vertex shader info*/
		ShaderInfo vshader_info;
		vshader_info.filePath = VTEXT("Basic.vs");
		vshader_info.raw = VTEXT("");
		vshader_info.type = ShaderType::VERTEX_SHADER;

		/*fragment shader info*/
		ShaderInfo fshader_info;
		fshader_info.filePath = VTEXT("Basic.fs");
		fshader_info.raw = VTEXT("");
		fshader_info.type = ShaderType::FRAGMENT_SHADER;

		/*populate shader args*/
		ShaderArgs args;
		args[0] = vshader_info;
		args[1] = fshader_info;

		/*create shader program*/
		m_program = new GLShaderProgram(args);
	}

	void PrimitiveTube::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;


		m_program->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_VIEW, viewLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_WORLD, worldLoc);

		Mat4 world = Mat4(0.0f);
		world =
			glm::translate(Mat4(1.0f), m_position) * //apply position
			glm::rotate(Mat4(1.0f), m_rotationX, Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationY, Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationZ, Vec3(0, 0, 1));

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
	}

	void PrimitiveTube::Render(GLCamera3D* camera)
	{
		m_program->Bind();

		applyTransform(camera);

		//RENDER TOP
		m_vBuffer->set(0, m_topVerts.size(), m_topVerts.data());
		m_vBuffer->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		PositionColor::Enable(true);
		PositionColor::RenderArrays(m_topVerts.size(), GL_QUAD_STRIP);
		PositionColor::Enable(false);
		m_vBuffer->unbind();


		//RENDER BOTTOM
		m_vBuffer->set(0, m_botVerts.size(), m_botVerts.data());
		m_vBuffer->bind();
		PositionColor::Enable(true);
		PositionColor::RenderArrays(m_botVerts.size(), GL_QUAD_STRIP);
		PositionColor::Enable(false);
		m_vBuffer->unbind();

		//RENDER MIDDLE
		m_vBuffer->set(0, m_inBodyVerts.size(), m_inBodyVerts.data());
		m_vBuffer->bind();
		PositionColor::Enable(true);
		PositionColor::RenderArrays(m_inBodyVerts.size(), GL_QUAD_STRIP);
		PositionColor::Enable(false);
		m_vBuffer->unbind();

		m_vBuffer->set(0, m_outBodyVerts.size(), m_outBodyVerts.data());
		m_vBuffer->bind();
		PositionColor::Enable(true);
		PositionColor::RenderArrays(m_outBodyVerts.size(), GL_QUAD_STRIP);
		PositionColor::Enable(false);
		m_vBuffer->unbind();

		//m_iBuffer->unbind();
		m_program->Unbind();
	}

}
