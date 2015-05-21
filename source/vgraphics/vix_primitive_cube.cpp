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

#include <vix_primitive_cube.h>
#include <vix_color.h>

namespace Vixen {

	PrimitiveCube::PrimitiveCube()
	{
		m_position = Vec3(0.0f);
		m_scale = Vec3(1.0f);
		m_rotation = Vec3(0.0f);
		m_color = Colors::White;
		m_vBuffer = new VBuffers::PCVBuffer(COLOR_VERT_COUNT);
		m_iBuffer = new GLIndexBuffer(COLOR_INDEX_COUNT);
		m_usingCustomWorld = false;

		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveCube::~PrimitiveCube()
	{
		delete m_vBuffer;
		delete m_program;
		delete m_iBuffer;
	}

	void PrimitiveCube::RotateX(float dt)
	{
		m_rotation.x += dt * 50.0f;
	}

	void PrimitiveCube::RotateY(float dt)
	{
		m_rotation.y += dt * 50.0f;
	}

	void PrimitiveCube::RotateZ(float dt)
	{
		m_rotation.z += dt * 50.0f;
	}

	void PrimitiveCube::SetPosition(Vec3& position)
	{
		m_position = position;
		m_usingCustomWorld = false;
	}

	void PrimitiveCube::SetScale(Vec3& scale)
	{
		m_scale = scale;
		m_usingCustomWorld = false;
	}

	void PrimitiveCube::SetRotation(Vec3& rotation)
	{
		m_rotation = rotation;
		m_usingCustomWorld = false;
	}


	void PrimitiveCube::SetWorldMatrix(Mat4& world)
	{
		m_world = world;
		m_usingCustomWorld = true;
	}

	void PrimitiveCube::SetColor(const Color& color)
	{
		m_color = color;
	}

	void PrimitiveCube::init_color_vi_buffers()
	{
		const std::array<PositionColor, COLOR_VERT_COUNT> vTemp =
		{
			PositionColor(-1.0f, 1.0f, 1.0f,
			   Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			PositionColor(1.0f, 1.0f, 1.0f,
			   Colors::Blue.r, Colors::Blue.g, Colors::Blue.b, Colors::Blue.a),
			PositionColor(-1.0f, -1.0f, 1.0f,
			   Colors::Yellow.r, Colors::Yellow.g, Colors::Yellow.b, Colors::Yellow.a),
			PositionColor(1.0f, -1.0f, 1.0f,
			   Colors::Pink.r, Colors::Pink.g, Colors::Pink.b, Colors::Pink.a),

			PositionColor(1.0f, 1.0f, -1.0f,
			   Colors::Green.r, Colors::Green.g, Colors::Green.b, Colors::Green.a),
			PositionColor(-1.0f, 1.0f, -1.0f,
			   Colors::Orange.r, Colors::Orange.g, Colors::Orange.b, Colors::Orange.a),
			PositionColor(1.0, -1.0f, -1.0f,
			   Colors::Aqua.r, Colors::Aqua.g, Colors::Aqua.b, Colors::Aqua.a),
			PositionColor(-1.0f, -1.0f, -1.0f,
			   Colors::Purple.r, Colors::Purple.g, Colors::Purple.b, Colors::Purple.a)
		};
		m_vBuffer->set(0, COLOR_VERT_COUNT, vTemp.data());

		const std::array<unsigned short, COLOR_INDEX_COUNT> iTemp =
		{
			//FRONT FACE
			0, 1, 3, 2,

			//BACK FACE
			4, 5, 7, 6,

			//LEFT FACE
			5, 0, 2, 7,

			//RIGHT FACE
			1, 4, 6, 3,

			//TOP FACE
			5, 4, 1, 0,

			//BOTTOM FACE
			6, 7, 2, 3
		};
		m_iBuffer->set(0, COLOR_INDEX_COUNT, iTemp.data());
	}

	void PrimitiveCube::init_shader_program()
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

	void PrimitiveCube::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;
		GLuint colorLoc;

		m_program->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_VIEW, viewLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_WORLD, worldLoc);
		m_program->GetUniformLoc("gColor", colorLoc);

		if(!m_usingCustomWorld) {
			Mat4 world = Mat4(0.0f);
			m_world =
				glm::translate(Mat4(1.0f), m_position) * //apply position
				glm::rotate(Mat4(1.0f), m_rotation.x, Vec3(1, 0, 0)) *
				glm::rotate(Mat4(1.0f), m_rotation.y, Vec3(0, 1, 0)) *
				glm::rotate(Mat4(1.0f), m_rotation.y, Vec3(0, 0, 1)) *
				glm::scale(Mat4(1.0f), m_scale);
		}

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(m_world));
		glUniform4f(colorLoc, m_color.r, m_color.g, m_color.b, m_color.a); 
	}

	void PrimitiveCube::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		PositionColor::Enable(true);
		PositionColor::RenderElements(COLOR_INDEX_COUNT, GL_QUADS);
		PositionColor::Enable(false);

		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_program->Unbind();
	}

}
