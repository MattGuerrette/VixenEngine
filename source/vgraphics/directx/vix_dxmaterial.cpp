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

namespace Vixen {

    DXMaterial::DXMaterial()
    {

    }

    DXMaterial::~DXMaterial()
    {
        STLMAP_DELETE(m_shaders);
        STLMAP_DELETE(m_textures);
    }

    void DXMaterial::VBind()
    {

    }

    void DXMaterial::VUnbind()
    {

    }


    void DXMaterial::VSetAmbientColor(Color color)
    {
        m_ambientColor = color;
    }

    void DXMaterial::VSetDiffuseColor(Color color)
    {
        m_diffuseColor = color;
    }

    void DXMaterial::VSetSpecularColor(Color color)
    {
        m_specularColor = color;
    }
    
    void DXMaterial::VSetSpecularWeight(float weight)
    {
        m_specularWeight = weight;
    }

    void DXMaterial::VSetAlphaTransparency(float transparency)
    {
        m_transparency = transparency;
    }

    void DXMaterial::VSetShader(IMaterial::ShaderRole role, IShader* shader)
    {
        m_shaders[role] = (DXShader*)shader;
    }

    void DXMaterial::VSetTexture(IMaterial::TextureRole role, ITexture* texture)
    {
        m_textures[role] = (DXTexture*)texture;
    }

    ITexture* DXMaterial::VGetTexture(IMaterial::TextureRole role)
    {
        //try and find texture matching role
        std::map<IMaterial::TextureRole, DXTexture*>::iterator it = m_textures.find(role);
        if (it != m_textures.end())
            return it->second;
        else
            return NULL;
    }

    IShader* DXMaterial::VGetShader(IMaterial::ShaderRole role)
    {
        //try and find shader matching role
        std::map<IMaterial::ShaderRole, DXShader*>::iterator it = m_shaders.find(role);
        if (it != m_shaders.end())
            return it->second;
        else
            return NULL;
    }

    DXTexture* DXMaterial::GetTexture(IMaterial::TextureRole role)
    {
        return (DXTexture*)VGetTexture(role);
    }

    DXShader* DXMaterial::GetShader(IMaterial::ShaderRole role)
    {
        return (DXShader*)VGetShader(role);
    }

}