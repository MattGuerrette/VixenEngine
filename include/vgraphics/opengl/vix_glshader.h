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
