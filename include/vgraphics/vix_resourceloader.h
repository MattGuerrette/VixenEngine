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
