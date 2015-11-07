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
#include <vix_asset.h>

namespace Vixen {

    class VIX_API Material : public Asset
    {
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

        enum class ShaderRole
        {
            Vertex,
            Pixel
        };

		Material();

        virtual ~Material() { };

        virtual void VBind() = 0;
        virtual void VUnbind() = 0;

		virtual UString VFilePath() = 0;
		
    };

}

#endif
