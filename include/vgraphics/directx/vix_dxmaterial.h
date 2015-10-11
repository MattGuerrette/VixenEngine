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
