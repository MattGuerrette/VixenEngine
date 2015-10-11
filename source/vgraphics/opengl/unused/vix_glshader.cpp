/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vix_glshader.h>
#include <vix_debugutil.h>

namespace Vixen {

	GLShader::GLShader(const ShaderInfo& info)
	{
		m_info = info;


		if (m_info.filePath.empty() && m_info.raw.empty()) {
			/*no file or raw contents avaliable for loading*/
			DebugPrintF(VTEXT("Shader creation failed: %s\n"),
				        VTEXT("No shader path or raw contents avaliable"));
		}

		/*determine if shader should load from file or raw contents*/
		bool success = false;
		if (!m_info.filePath.empty()) {
			success = VInitFromFile(m_info.filePath);
		}
		else {
			success = VInitFromString(m_info.raw);
		}

		if (!success) {
			DebugPrintF(VTEXT("Shader creation failed\n"));
		}
	}

	GLShader::~GLShader()
	{
		glDeleteShader(m_shader);
	}

	bool GLShader::VInitFromFile(File* file)
	{
		return true;
	}

	bool GLShader::LoadShader(const GLchar* source)
	{


		GLenum type = GLShaderType(m_info.type);
		if (type == GL_NONE) {
			DebugPrintF(VTEXT("Failed to Load Shader due to invalid type\n"));
			return false;
		}

		/*create shader object*/
		m_shader = glCreateShader(type);

		/*put shader source into memory*/
		glShaderSource(m_shader, 1, &source, NULL);
		/*cleanup allocated source*/

		/*compile shader*/
		glCompileShader(m_shader);
		ValidateCompile(m_shader);

		return true;
	}

	bool GLShader::ValidateCompile(GLuint shader)
	{

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLsizei length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			/*output shader log info*/
			GLchar* log = new GLchar[length + 1];
			glGetShaderInfoLog(shader, length, &length, log);
#ifdef UNICODE
			std::string log_text(log);
			UConverter converter;
			UString log_string = converter.from_bytes(log_text);
			DebugPrintF(log_string.c_str());
			std::cout << log << std::endl;
#else
			DebugPrintF(VTEXT("Shader Log: %s\n"),
				    log);
#endif
			delete[] log;

			return false;
		}


		return true;
	}

	const GLchar* GLShader::ReadShader(const UString& path)
	{
		FILE* file;
#if defined VIX_SYS_WINDOWS && defined UNICODE
		_wfopen_s(&file, path.c_str(), VTEXT("rb"));
#else
		file = fopen(path.c_str(), VTEXT("rb"));
#endif
		if (!file) {
			DebugPrintF(VTEXT("Unabled to read shader\n"));
			return NULL;
		}

		/*seek end of file*/
		fseek(file, 0, SEEK_END);
		/*cache length*/
		size_t len = ftell(file);
		/*seek beg of file*/
		fseek(file, 0, SEEK_SET);

		/*buffer source*/
		GLchar* src = new GLchar[len + 1];

		/*read file contents into buffer*/
		fread(src, 1, len, file);
		/*close file after read*/
		fclose(file);
		/*null terminate*/
		src[len] = 0;

		return src;
	}

	GLenum GLShader::GLShaderType(ShaderType type)
	{
		switch (type)
		{
		case Vixen::ShaderType::VERTEX_SHADER:
			return GL_VERTEX_SHADER;
			break;
		case Vixen::ShaderType::GEOMETRY_SHADER:
			return GL_GEOMETRY_SHADER;
			break;
		case Vixen::ShaderType::TESSELATION_CONTROL_SHADER:
			return GL_TESS_CONTROL_SHADER;
			break;
		case Vixen::ShaderType::TESSELATION_EVAL_SHADER:
			return GL_TESS_EVALUATION_SHADER;
			break;
		case Vixen::ShaderType::FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;
			break;
		}

		return GL_NONE;
	}

	GLuint GLShader::ShaderHandle() const
	{
		return m_shader;
	}
}
