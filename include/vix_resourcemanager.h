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

#ifndef VIX_RESOURCEMANAGER_H
#define VIX_RESOURCEMANAGER_H

#include "vix_platform.h"
#include "vix_filemanager.h"
#include "vix_resourceloader.h"
#include "vix_texture.h"
#include "vix_shader.h"
#include "vix_model.h"
#include "vix_font.h"
#include "vix_material.h"

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
        Shader,
		Material
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
        static Texture*    OpenTexture(UString filePath);
        static Shader*     OpenShader(UString filePath, ShaderType type);
        static Model*      OpenModel(UString filePath);
        static Font*       OpenFont(UString filePath);
        static Material*   OpenMaterial(UString filePath);

		static Asset*		AccessAsset(UString assetName);
		static void			MapAsset(UString assetName, Asset* asset);
		static void			ReleaseAsset(Asset* asset);


		static uint32_t     NumLoadedModels();
		static Model*		ModelAsset(uint32_t index);

		static std::map<UString, Model*>& LoadedModels();

        static void         IncrementAssetRef(Asset* asset);
        static void         DecrementAssetRef(Asset* asset);

		static void			PrintLoaded();

    private:
        IResourceLoader* m_resourceLoader;

		std::map<UString, Asset*> m_assetMap;
		std::map<UString, Model*> m_models;
    };




}

#endif
