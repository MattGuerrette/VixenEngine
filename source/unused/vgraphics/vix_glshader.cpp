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

#include <vix_glshader.h>
#include <vix_debugutil.h>
#include <vix_errglobals.h>

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
		bool success;
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

	bool GLShader::VInitFromFile(const UString& path)
	{
		/*grab source from file*/
		const GLchar* source = ReadShader(path);
		if (!source) {
			DebugPrintF(VTEXT("Failed to parse shader source\n"));
			return false;
		}

		if (!LoadShader(source)) {
			DebugPrintF(VTEXT("Failed to init shader from file\n"));
			return false;
		}

		return true;
	}

	bool GLShader::VInitFromString(const UString& path)
	{

#if defined UNICODE && defined VIX_SYS_WINDOWS
		UConverter cv;
		std::string _source = cv.to_bytes(m_info.raw.c_str());
		const GLchar* source = _source.c_str();
#else
		const GLchar* source = (const GLchar*)m_info.raw.c_str();
#endif
		if (!LoadShader(source)) {
			if (CheckError(error)) {
				DebugPrintF(VTEXT("Failed to init shader from source\n"));
				return true;
			}
		}

		return false;
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

		return ValidateCompile(m_shader);
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
			DebugPrintF(VTEXT("Unabled to read shader: %s\n"),
				    ErrCodeString(ErrCode::ERR_FAILURE).c_str());
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
