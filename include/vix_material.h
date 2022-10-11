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

#ifndef VIX_MATERIAL_H
#define VIX_MATERIAL_H

#include "vix_platform.h"
#include "vix_containers.h"
#include "vix_texture.h"
#include "vix_shader.h"
#include "vix_color.h"
#include "vix_asset.h"
#include "vix_tinyxml.h"
#include "vix_shadervariable.h"

namespace Vixen {

    class VIX_API Material : public Asset
    {
		typedef std::map<std::string, IShaderVariable*> VariableMap;
    public:
        enum class TextureRole
        {
            Diffuse,
            Ambient,
            SpecularColor,
            SpecularHighlight,
            Alpha,
            Normal,
            Displacement,
            Decal
        };

        enum ShaderRole
        {
            Vertex = 0,
            Pixel = 1
        };

		Material();

        virtual ~Material() { };

        virtual void VBind() = 0;
        virtual void VUnbind() = 0; 

		virtual UString VFilePath() = 0;

		void SetShaderVariableFloat(ShaderRole shader, std::string name, float val);
		void SetShaderVariableFloat4(ShaderRole shader, std::string name, float x, float y, float z, float w);
		void SetShaderVariableInt(ShaderRole shader, std::string name, int val);
		void SetShaderVariableMatrix4(ShaderRole shader, std::string name, const float val[16]);

	protected:
		VariableMap								m_vsVariables;
		VariableMap								m_psVariables;
		
		static bool ReadShaderChildren(tinyxml2::XMLElement* shaderElement, VariableMap& variableMap);
    };

}

#endif
