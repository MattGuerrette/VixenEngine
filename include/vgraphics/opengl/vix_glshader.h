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

#ifndef VIX_GLSHADER_H
#define VIX_GLSHADER_H

#include <vix_platform.h>
#include <vix_shader.h>
#include <vix_stringutil.h>
#include <vix_gl.h>

namespace Vixen {

	class VIX_API GLShader : public IShader
	{
	public:
		GLShader(const ShaderInfo& info);

		~GLShader();

		bool VInitFromFile(File* file);

		GLuint ShaderHandle() const;

	protected:
		void VBind() = 0;
        void VUnbind() = 0;

	private:

		bool  					LoadShader(const GLchar* source);
		static const GLchar* 	ReadShader(const UString& path);
		static GLenum        	GLShaderType(ShaderType type);
		static bool       		ValidateCompile(GLuint shader);

	private:
		GLuint     m_shader;
		ShaderInfo m_info;
	};

}

#endif
