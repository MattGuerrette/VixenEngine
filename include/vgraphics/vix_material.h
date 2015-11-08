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

#ifndef VIX_MATERIAL_H
#define VIX_MATERIAL_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_texture.h>
#include <vix_shader.h>
#include <vix_color.h>
#include <vix_asset.h>
#include <vix_tinyxml.h>
#include <vix_shadervariable.h>

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