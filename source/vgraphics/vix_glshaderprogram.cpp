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

#include <vix_glshaderprogram.h>
#include <vix_debugutil.h>

namespace Vixen {

	GLShaderProgram::GLShaderProgram(const ShaderArgs args)
	{
		m_args = args;
		m_vShader = NULL;
		m_fShader = NULL;
		m_tcShader = NULL;
		m_teShader = NULL;
		m_program = glCreateProgram();

		/*load and create shaders from args*/
		ErrCode error = VCreateShadersFromArgs();
		if (CheckError(error)) {
		  DebugPrintF(VTEXT("Failed to create shader program"));
		}
		else {
			//DebugPrintF(VTEXT("Created shader program"));
		}
	}

	GLShaderProgram::~GLShaderProgram()
	{
		glDeleteProgram(m_program);
	}

	void GLShaderProgram::Bind()
	{
		glUseProgram(m_program);
	}

	void GLShaderProgram::Unbind()
	{
		glUseProgram(NULL);
	}

	ErrCode GLShaderProgram::VCreateShadersFromArgs()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;


		/*iterate over shader info objects*/

		for (auto& info : m_args) {
			switch (info.type)
			{
			case ShaderType::VERTEX_SHADER:
				if (!m_vShader) {
					m_vShader = new GLShader(info);
					AttachShader(m_vShader);
					LinkShader(m_vShader);
				}
				break;

			case ShaderType::TESSELATION_CONTROL_SHADER:
				if(!m_tcShader) {
					m_tcShader = new GLShader(info);
					AttachShader(m_tcShader);
					LinkShader(m_tcShader);
				}
				break;

			case ShaderType::TESSELATION_EVAL_SHADER:
				if(!m_teShader) {
					m_teShader = new GLShader(info);
					AttachShader(m_teShader);
					LinkShader(m_teShader);
				}
				break;

			case ShaderType::GEOMETRY_SHADER:
				if(!m_gShader) {
					m_gShader = new GLShader(info);
					AttachShader(m_gShader);
					LinkShader(m_gShader);
				}
				break;

			case ShaderType::FRAGMENT_SHADER:
				if (!m_fShader) {
					m_fShader = new GLShader(info);
					AttachShader(m_fShader);
					LinkShader(m_fShader);
				}
				break;
			default:
				break;
			}
		}

		return error;
	}

	void GLShaderProgram::AttachShader(Shader* shader)
	{
		if (shader) {
			glAttachShader(m_program, ((GLShader*)shader)->ShaderHandle());
		}
	}

	ErrCode GLShaderProgram::GetUniformLoc(const GLchar* name, GLuint& location)
	{
		location = glGetUniformLocation(m_program, name);
		if (location < 0) {
			return ErrCode::ERR_FAILURE;
		}

		return ErrCode::ERR_SUCCESS;
	}

	ErrCode GLShaderProgram::LinkShader(Shader* shader)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*link program to shader*/
		glLinkProgram(m_program);
		//error = ValidateCompile(m_program);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Failed to link shader to program"));
			delete shader;
		}

		return error;
	}

	ErrCode GLShaderProgram::ValidateCompile(GLuint program)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			error = ErrCode::ERR_FAILURE;

			GLsizei length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			GLchar* log = new GLchar[length + 1];
			glGetProgramInfoLog(program, length, &length, log);
			DebugPrintF(VTEXT("Program Log: %s\n"),
				log);
			delete[] log;
		}

		return error;
	}
}
