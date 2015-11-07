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

#ifndef VIX_DXMATERIAL_H
#define VIX_DXMATERIAL_H

#include <vix_platform.h>
#include <vix_material.h>
#include <vix_dxtexture.h>
#include <vix_dxshader.h>
#include <vix_shadervariable.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_tinyxml.h>

namespace Vixen {

	

    class VIX_API DXMaterial : public Material
    {
		typedef std::map<std::string, IShaderVariable*> VariableMap;
    public:
        DXMaterial();

        ~DXMaterial();

<<<<<<< HEAD


=======
>>>>>>> 7e4502b797e001a298b2a224c9fc4b4dcc75a61d
        void VBind();
        void VUnbind();

		DXVertexShader* GetVertexShader();
		

		bool VInitFromFile(File* file);

		UString VFilePath();

    private:
		VariableMap								m_vsVariables;
		VariableMap								m_psVariables;
        std::map<ShaderRole,  DXShader*>		m_shaders;
		UString									m_path;

	private:
		static bool ReadShaderChildren(tinyxml2::XMLElement* shaderElement, VariableMap& variableMap);
    };

}

#endif
