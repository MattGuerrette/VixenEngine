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

#ifndef VIX_MATERIAL_H
#define VIX_MATERIAL_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_texture.h>
#include <vix_shader.h>
#include <vix_color.h>

namespace Vixen {

    class VIX_API IMaterial
    {
    public:
        enum class TextureRole
        {
            Diffuse,
            Ambient,
            SpecularColor,
            SpecularHighlight,
            Alpha,
            Bump,
            Displacement,
            Decal
        };

        enum class ShaderRole
        {
            Vertex,
            Pixel
        };


        virtual ~IMaterial() { };

        virtual void VBind() = 0;
        virtual void VUnbind() = 0;

        virtual ITexture* VGetTexture(TextureRole role) = 0;
        virtual IShader*  VGetShader(ShaderRole role) = 0;

        virtual void VSetAmbientColor(Color color) = 0;
        virtual void VSetDiffuseColor(Color color) = 0;
        virtual void VSetSpecularColor(Color color) = 0;
        virtual void VSetSpecularWeight(float weight) = 0;
        virtual void VSetAlphaTransparency(float transparency) = 0;
        virtual void VSetTexture(TextureRole role, ITexture* texture) = 0;
        virtual void VSetShader(ShaderRole role, IShader* shader) = 0;

    };

}

#endif
