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

#ifndef VIX_GLSHADERPROGRAM_H
#define VIX_GLSHADERPROGRAM_H

#include <vix_platform.h>
#include <vix_shaderprogram.h>
#include <vix_glshader.h>

#define SHADER_GLOBAL_PROJECTION "gProjection"
#define SHADER_GLOBAL_WORLD      "gWorld"
#define SHADER_GLOBAL_VIEW       "gView"

namespace Vixen {

	class VIX_API GLShaderProgram : public ShaderProgram
	{
	public:
		GLShaderProgram(const ShaderArgs args);

		~GLShaderProgram();

		/*bind gl program to render pipeline*/
		void Bind();

		/*unbind gl program from render pipeline*/
		void Unbind();

		/*retrive uniform location*/
		bool GetUniformLoc(const GLchar* name, GLuint& location);

	protected:
		bool VCreateShadersFromArgs() override;

		/*attach OpenGL shader to program*/
		void    AttachShader(Shader* shader);


		/*try and OpenGL link shader to program*/
		bool LinkShader(Shader* shader);

	private:
		GLuint m_program;


		static bool  ValidateCompile(GLuint program);
	};
}

#endif
