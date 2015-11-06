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

#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>
#include <vix_renderer_singleton.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxresourceloader.h>
#endif

namespace Vixen {

    ResourceManager::~ResourceManager()
    {

    }

    bool ResourceManager::Initialize()
    {
        ResourceManager& _manager = ResourceManager::instance();

#ifdef VIX_SYS_WINDOWS
        _manager.m_resourceLoader = new DXResourceLoader((DXRenderer*)Renderer::Handle());
#endif

        return true;
    }

    void ResourceManager::DeInitialize()
    {
        ResourceManager& _manager = ResourceManager::instance();

        delete _manager.m_resourceLoader;
    }

    void ResourceManager::AttachResourceLoader(IResourceLoader* loader)
    {
        ResourceManager& _RM = ResourceManager::instance();

        _RM.m_resourceLoader = loader;
    }

    ITexture* ResourceManager::OpenTexture(UString filePath)
    {
        UString assetPath = PathManager::AssetPath() + VTEXT("Textures/");

        assetPath += filePath;
        assetPath = os_path(assetPath);

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

            if(_RM.m_resourceLoader)
                return _RM.m_resourceLoader->LoadTexture(file);

        }

        return NULL;
    }

    IShader* ResourceManager::OpenShader(UString filePath, ShaderType type)
    {
        UString assetPath = PathManager::ShaderPath();

        assetPath += filePath;
        assetPath = os_path(assetPath);

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
               IShader* _shader = _RM.m_resourceLoader->LoadShader(file, type);
               FileManager::CloseFile(assetPath);
               return _shader;
            }


        }

        return NULL;
    }

    IModel* ResourceManager::OpenModel(UString filePath)
    {
        UString assetPath = PathManager::ModelPath();

        assetPath += filePath;
        assetPath = os_path(assetPath);

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific model type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
                //Need to load a model object into memory
                IModel* _model = _RM.m_resourceLoader->LoadModel(file);
                FileManager::CloseFile(assetPath);
                return _model;
            }
        }

        return NULL;
    }

    IFont* ResourceManager::OpenFont(UString filePath)
    {
        UString assetPath = PathManager::AssetPath() + VTEXT("Fonts/");

        assetPath += filePath;
        assetPath = os_path(assetPath);

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific model type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
                //Need to load a model object into memory
                IFont* _font = _RM.m_resourceLoader->LoadFont(file);
                FileManager::CloseFile(file);
                return _font;
            }
        }

        return NULL;
    }

}
