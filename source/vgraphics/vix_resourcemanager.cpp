/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

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

	IMaterial* ResourceManager::OpenMaterial(UString filePath)
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
				//Need to load a material object into memory
				IMaterial* _material = _RM.m_resourceLoader->LoadMaterial(file);
				FileManager::CloseFile(file);
				return _material;
			}
		}

		return NULL;
	}

}
