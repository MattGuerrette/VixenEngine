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
