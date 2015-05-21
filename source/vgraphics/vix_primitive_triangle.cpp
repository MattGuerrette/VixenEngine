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

#include <vix_primitive_triangle.h>
#include <vix_color.h>
#include <array>

namespace Vixen {

	PrimitiveTriangle::PrimitiveTriangle()
	{
		m_rotation = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VBuffers::PCVBuffer(VERTEX_COUNT);
		m_iBuffer = new GLIndexBuffer(INDEX_COUNT);

		const std::array<PositionColor, VERTEX_COUNT> vTemp =
		{
			PositionColor(0.0f, 1.0f, 0.0f,
								Colors::Red.r, Colors::Red.g, Colors::Red.b, 1.0f),
			PositionColor(1.0f, -1.0f, 0.0f,
			                    Colors::Blue.r, Colors::Blue.g, Colors::Blue.b, 1.0f),
			PositionColor(-1.0f, -1.0f, 0.0f,
			                    Colors::Green.r, Colors::Green.g, Colors::Green.b, 1.0f)
		};
		m_vBuffer->set(0, VERTEX_COUNT, vTemp.data());

		const std::array<unsigned short, INDEX_COUNT> iTemp =
		{
			0, 1, 2
		};
		m_iBuffer->set(0, INDEX_COUNT, iTemp.data());

		init_shader_program();

	}

	PrimitiveTriangle::~PrimitiveTriangle()
	{
		delete m_vBuffer;
		delete m_program;
		delete m_iBuffer;
	}

	void PrimitiveTriangle::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}

	void PrimitiveTriangle::Rotate(float dt)
	{
		m_rotation += dt * 5.0f;
	}

	void PrimitiveTriangle::init_shader_program()
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

	void PrimitiveTriangle::applyTransform(GLCamera3D* camera)
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
			glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 1, 0));

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
	}

	void PrimitiveTriangle::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		PositionColor::Enable(true);
		PositionColor::RenderElements(INDEX_COUNT, GL_TRIANGLES);
		PositionColor::Enable(false);

		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_program->Unbind();
	}

}
