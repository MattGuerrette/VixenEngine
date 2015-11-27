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

#ifndef VIX_SHADERPROGRAM_H
#define VIX_SHADERPROGRAM_H

#include <vix_platform.h>
#include <vix_shader.h>
#include <array>

namespace Vixen {

	typedef std::array<ShaderInfo, 5> ShaderArgs;

	class VIX_API ShaderProgram
	{
	public:
		virtual ~ShaderProgram() { };

	protected:

		virtual bool VCreateShadersFromArgs() = 0;

	protected:
		ShaderArgs m_args;     /*collection of shader info*/
		Shader*    m_vShader;  /*vertex shader*/
		Shader*    m_fShader;  /*fragment shader*/
		Shader*    m_gShader;  /*geometry shader*/
		Shader*    m_tcShader; /*tess control shader*/
		Shader*    m_teShader; /*tess eval shader*/
	};

}

#endif
