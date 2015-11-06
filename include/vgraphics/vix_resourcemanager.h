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

#ifndef VIX_RESOURCEMANAGER_H
#define VIX_RESOURCEMANAGER_H

#include <vix_platform.h>
#include <vix_filemanager.h>
#include <vix_resourceloader.h>
#include <vix_texture.h>
#include <vix_shader.h>
#include <vix_model.h>
#include <vix_font.h>
#include <vix_material.h>

namespace Vixen {



    /**
    *   ResourceType enum class
    *
    *   Defines the different available resource types
    *   usable by Vixen Game Engine
    */
    enum class ResourceType
    {
        Texture,
        Model,
        Font,
        Shader
    };

    /**
    *   ResourceManager class
    *
    *   Defines the resource manager object that is used to load
    *   game content into the Vixen Game Engine at runtime.
    */
    class VIX_API ResourceManager : public Singleton<ResourceManager>
    {
    public:
        ~ResourceManager();

        static bool Initialize();

        static void DeInitialize();

        static void         AttachResourceLoader(IResourceLoader* loader);
        static ITexture*    OpenTexture(UString filePath);
        static IShader*     OpenShader(UString filePath, ShaderType type);
        static IModel*      OpenModel(UString filePath);
        static IFont*       OpenFont(UString filePath);
        static IMaterial*   OpenMaterial(UString filePath);

    private:
        IResourceLoader* m_resourceLoader;
    };




}

#endif
