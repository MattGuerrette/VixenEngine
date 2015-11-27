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

#include <vix_material.h>
#include <vix_tinyxml.h>
#include <vix_resourcemanager.h>

namespace Vixen {

	Material::Material()
		: Asset()
	{

	}

	void Material::SetShaderVariableFloat(ShaderRole shader, std::string name, float val)
	{
		switch (shader)
		{
		case ShaderRole::Vertex:
			((FloatVariable*)m_vsVariables[name])->SetData(val);
			break;
		case ShaderRole::Pixel:
			((FloatVariable*)m_psVariables[name])->SetData(val);
			break;
		}
	}

	void Material::SetShaderVariableFloat4(ShaderRole shader, std::string name, float x, float y, float z, float w)
	{
		switch (shader)
		{
		case ShaderRole::Vertex:
			((Float4Variable*)m_vsVariables[name])->SetData(x, y, z, w);
			break;
		case ShaderRole::Pixel:
			((Float4Variable*)m_psVariables[name])->SetData(x, y, z, w);
			break;
		}
	}

	void Material::SetShaderVariableInt(ShaderRole shader, std::string name, int val)
	{
		switch (shader)
		{
		case ShaderRole::Vertex:
			((IntVariable*)m_vsVariables[name])->SetData(val);
			break;
		case ShaderRole::Pixel:
			((IntVariable*)m_psVariables[name])->SetData(val);
			break;
		}
	}

	void Material::SetShaderVariableMatrix4(ShaderRole shader, std::string name, const float val[16])
	{
		switch (shader)
		{
		case ShaderRole::Vertex:
			((Matrix4FloatVariable*)m_vsVariables[name])->SetData(val);
			break;
		case ShaderRole::Pixel:
			((Matrix4FloatVariable*)m_psVariables[name])->SetData(val);
			break;
		}
	}


	bool Material::ReadShaderChildren(tinyxml2::XMLElement* shaderElement, Material::VariableMap& variableMap)
	{
		using namespace tinyxml2;

		XMLElement* shaderChild = shaderElement->FirstChildElement();
		while (shaderChild)
		{
			//read all child data for pixel shader
			std::string _name = shaderChild->Name();
			if (_name == "float") {
				//read float
				std::string key = shaderChild->Attribute("name");
				float val = shaderChild->FloatAttribute("val");

				variableMap[key] = new FloatVariable(val);
			}

			if (_name == "vec4") {
				//read vec4

				std::string key = shaderChild->Attribute("name");
				float x = shaderChild->FloatAttribute("x");
				float y = shaderChild->FloatAttribute("y");
				float z = shaderChild->FloatAttribute("z");
				float w = shaderChild->FloatAttribute("w");

				variableMap[key] = new Float4Variable(x, y, z, w);
			}

			if (_name == "int") {
				//read vec4

				std::string key = shaderChild->Attribute("name");
				float val = shaderChild->FloatAttribute("val");

				variableMap[key] = new IntVariable(val);
			}

			if (_name == "mat4") {
				//read vec4

				std::string key = shaderChild->Attribute("name");
				float a1 = shaderChild->FloatAttribute("a1");
				float a2 = shaderChild->FloatAttribute("a2");
				float a3 = shaderChild->FloatAttribute("a3");
				float a4 = shaderChild->FloatAttribute("a4");
				float b1 = shaderChild->FloatAttribute("b1");
				float b2 = shaderChild->FloatAttribute("b2");
				float b3 = shaderChild->FloatAttribute("b3");
				float b4 = shaderChild->FloatAttribute("b4");
				float c1 = shaderChild->FloatAttribute("c1");
				float c2 = shaderChild->FloatAttribute("c2");
				float c3 = shaderChild->FloatAttribute("c3");
				float c4 = shaderChild->FloatAttribute("c4");
				float d1 = shaderChild->FloatAttribute("d1");
				float d2 = shaderChild->FloatAttribute("d2");
				float d3 = shaderChild->FloatAttribute("d3");
				float d4 = shaderChild->FloatAttribute("d4");
				float val[16] = { a1, a2, a3, a4,
									b1, b2, b3, b4,
									c1, c2, c3, c4,
									d1, d2, d3, d4 };

				variableMap[key] = new Matrix4FloatVariable(val);
			}

			if (_name == "texture") {
				//read texture

				std::string key = shaderChild->Attribute("name");
				std::string fileName = shaderChild->Attribute("file");

				Texture* texture = ResourceManager::OpenTexture(UStringFromCharArray(fileName.c_str()));
				if (!texture) {
					return false;
				}

				variableMap[key] = new TextureVariable(texture);
			}

			shaderChild = shaderChild->NextSiblingElement();
		}

		return true;
	}
}
