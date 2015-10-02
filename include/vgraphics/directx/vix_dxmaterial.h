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

#ifndef VIX_DXMATERIAL_H
#define VIX_DXMATERIAL_H

#include <vix_platform.h>
#include <vix_material.h>
#include <vix_dxtexture.h>
#include <vix_dxshader.h>

namespace Vixen {

    class VIX_API DXMaterial : public IMaterial
    {
    public:
        DXMaterial();

        ~DXMaterial();

        

        void VBind();
        void VUnbind();

        ITexture* VGetTexture(TextureRole role);
        IShader*  VGetShader(ShaderRole role);

        DXTexture* GetTexture(TextureRole role);
        DXShader*  GetShader(ShaderRole role);

        void VSetAmbientColor(Color color);
        void VSetDiffuseColor(Color color);
        void VSetSpecularColor(Color color);
        void VSetSpecularWeight(float weight);
        void VSetAlphaTransparency(float transparency);
        void VSetTexture(TextureRole role, ITexture* texture);
        void VSetShader(ShaderRole role, IShader* shader);

    private:
        Color                             m_ambientColor;
        Color                             m_diffuseColor;
        Color                             m_specularColor;
        float                             m_specularWeight;
        float                             m_transparency;
        std::map<TextureRole, DXTexture*> m_textures;
        std::map<ShaderRole, DXShader*>   m_shaders;
    };

}

#endif