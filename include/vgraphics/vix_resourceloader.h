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

#ifndef VIX_RESOURCELOADER_H
#define VIX_RESOURCELOADER_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_texture.h>
#include <vix_shader.h>
#include <vix_model.h>
#include <vix_material.h>
#include <vix_font.h>

namespace Vixen {

    class VIX_API IResourceLoader
    {
    public:
        virtual ~IResourceLoader() { }

        virtual Texture*   LoadTexture(File* file) = 0;
        virtual Shader*    LoadShader(File* file, ShaderType type) = 0;
        virtual Model*     LoadModel(File* file) = 0;
        virtual Font*      LoadFont(File* file) = 0;
		virtual Material*  LoadMaterial(File* file) = 0;
      

    };

}

#endif
