/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

#include <vix_dxmaterial.h>
#include <vix_assimp.h>
#include <vix_tinyxml.h>
#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>
#include <vix_shader.h>

namespace Vixen {

    DXMaterial::DXMaterial()
        : Asset()
    {

    }

    DXMaterial::~DXMaterial()
    {
        STLMAP_DELETE(m_shaders);
		STLMAP_DELETE(m_vsVariables);
		STLMAP_DELETE(m_psVariables);
    }

	UString DXMaterial::VFilePath()
	{
		return m_path;
	}

    void DXMaterial::VBind()
	{
		for (auto& vsVariable : m_vsVariables)
			vsVariable.second->VBind(vsVariable.first, m_shaders[ShaderRole::Vertex]);
		for (auto& psVariable : m_psVariables)
			psVariable.second->VBind(psVariable.first, m_shaders[ShaderRole::Pixel]);

		//activate all shaders
		m_shaders[ShaderRole::Vertex]->Activate();
		m_shaders[ShaderRole::Pixel]->Activate();
    }

    void DXMaterial::VUnbind()
    {

    }

	DXVertexShader* DXMaterial::GetVertexShader()
	{
		return (DXVertexShader*)m_shaders[ShaderRole::Vertex];
	}


	bool DXMaterial::VInitFromFile(File* file)
	{
		if (!file)
			return false;

		//need to parse .VMT file and load material data

		using namespace tinyxml2;

		m_path = file->FileName();


		XMLDOC document;
		XMLError err = document.LoadFile(file->Handle());
		UString errString;
		if (XMLErrCheck(err, errString))
		{
			DebugPrintF(VTEXT("Vixen Material File: %s failed to load\n"), file->BaseName().c_str());
			return false;
		}

		XMLElement* matElement = document.FirstChildElement("material");

		//PARSE VERTEX SHADER
		XMLElement* vsElement = matElement->FirstChildElement("vertex-shader");
		if (!vsElement) {
			DebugPrintF(VTEXT("Vixen Material File: %s, missing vertex-shader"), file->BaseName().c_str());
			return false;
		}

		UString shaderPath = UStringFromCharArray(vsElement->Attribute("file"));
		IShader* vsShader = ResourceManager::OpenShader(shaderPath, ShaderType::VERTEX_SHADER);
		if (!vsShader)
			return false;
		m_shaders[ShaderRole::Vertex] = (DXShader*)vsShader;

		if (!ReadShaderChildren(vsElement, m_vsVariables))
			return false;

		//PARSE PIXEL SHADER
		XMLElement* psElement = matElement->FirstChildElement("pixel-shader");
		if (!psElement) {
			DebugPrintF(VTEXT("Vixen Material File: %s, missing pixel-shader"), file->BaseName().c_str());
			return false;
		}

		shaderPath = UStringFromCharArray(psElement->Attribute("file"));
		IShader* psShader = ResourceManager::OpenShader(shaderPath, ShaderType::PIXEL_SHADER);
		if (!psShader)
			return false;
		m_shaders[ShaderRole::Pixel] = (DXShader*)psShader;

		if (!ReadShaderChildren(psElement, m_psVariables))
			return false;
		
		return true;
	}

	bool DXMaterial::ReadShaderChildren(tinyxml2::XMLElement* shaderElement, DXMaterial::VariableMap& variableMap)
	{
		using namespace tinyxml2;

		XMLElement* shaderChild = shaderElement->FirstChildElement();
		while (shaderChild)
		{
			//read all child data for pixel shader
			std::string _name = shaderChild->Name();
			if (_name == "texture") {
				//read texture

				std::string key = shaderChild->Attribute("name");
				std::string fileName = shaderChild->Attribute("file");

				ITexture* texture = ResourceManager::OpenTexture(UStringFromCharArray(fileName.c_str()));
				if (!texture) {
					return false;
				}

				variableMap[key] = new TextureVariable(texture);
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

			shaderChild = shaderChild->NextSiblingElement();
		}

		return true;
	}
}