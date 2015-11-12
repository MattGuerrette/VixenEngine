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

    Texture* ResourceManager::OpenTexture(UString filePath)
    {
        UString assetPath = PathManager::AssetPath() + VTEXT("Textures/");

        assetPath += filePath;
        assetPath = os_path(assetPath);

		Texture* _texture = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

			if (_RM.m_resourceLoader)
			{
				_texture = (Texture*)ResourceManager::AccessAsset(file->FileName());

				if (!_texture)
				{
					_texture = _RM.m_resourceLoader->LoadTexture(file);

					ResourceManager::MapAsset(file->FileName(), (Asset*)_texture);

				}
				
				FileManager::CloseFile(file);
			}
               
            
        }

		return _texture;
    }

    Shader* ResourceManager::OpenShader(UString filePath, ShaderType type)
    {
        UString assetPath = PathManager::ShaderPath();

        assetPath += filePath;
        assetPath = os_path(assetPath);

		Shader* _shader = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
				_shader = (Shader*)ResourceManager::AccessAsset(file->FileName());

				if (!_shader)
				{
					_shader = _RM.m_resourceLoader->LoadShader(file, type);

					ResourceManager::MapAsset(file->FileName(), _shader);
				}
              
               FileManager::CloseFile(assetPath);
            }
        }

        return _shader;
    }

    Model* ResourceManager::OpenModel(UString filePath)
    {
        UString assetPath = PathManager::ModelPath();

        assetPath += filePath;
        assetPath = os_path(assetPath);

		Model* _model = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific model type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
				_model = (Model*)ResourceManager::AccessAsset(file->FileName());

				if (!_model)
				{
					//Need to load a model object into memory
					_model = _RM.m_resourceLoader->LoadModel(file);

					_RM.m_models[file->FileName()] = _model;

					ResourceManager::MapAsset(file->FileName(), _model);
				}

				FileManager::CloseFile(file);
            }
        }

        return _model;
    }

    Font* ResourceManager::OpenFont(UString filePath)
    {
        UString assetPath = PathManager::AssetPath() + VTEXT("Fonts/");

        assetPath += filePath;
        assetPath = os_path(assetPath);

		Font* _font = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific model type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
				_font = (Font*)ResourceManager::AccessAsset(file->FileName());

				if (!_font)
				{
					//Need to load a font object into memory
					_font = _RM.m_resourceLoader->LoadFont(file);
				
					ResourceManager::MapAsset(file->FileName(), _font);
				}

                FileManager::CloseFile(file);
            }
        }

        return _font;
    }

	Material* ResourceManager::OpenMaterial(UString filePath)
	{
		UString assetPath = PathManager::MaterialPath();

		assetPath += filePath;
		assetPath = os_path(assetPath);

		Material* _material = NULL;

		File* file = FileManager::OpenFile(assetPath);
		if (file)
		{
			//Create Renderer Specific model type
			ResourceManager& _RM = ResourceManager::instance();

			if (_RM.m_resourceLoader)
			{
				_material = (Material*)ResourceManager::AccessAsset(file->FileName());

				if (!_material)
				{
					//Need to load a material object into memory
					_material = _RM.m_resourceLoader->LoadMaterial(file);

					
					ResourceManager::MapAsset(file->FileName(), _material);
				}
				
				FileManager::CloseFile(file);
			}
		}

		return _material;
	}

	Asset* ResourceManager::AccessAsset(UString assetName)
	{
		ResourceManager& _RM = ResourceManager::instance();
		
		std::map<UString, Asset*>::iterator it;

		it = _RM.m_assetMap.find(assetName);
		if (it != _RM.m_assetMap.end())
			return it->second;
		else
			return NULL;
	}

	void ResourceManager::MapAsset(UString assetName, Asset* asset)
	{
		ResourceManager& _RM = ResourceManager::instance();

		asset->SetFileName(assetName);
		_RM.m_assetMap[assetName] = asset;
	}

	void ResourceManager::ReleaseAsset(Asset* asset)
	{
		if (!asset)
			return;

		if (asset->RefCount() <= 0)
			delete asset;
		else
			asset->DecrementRefCount();
	}

	std::map<UString, Model*>& ResourceManager::LoadedModels()
	{
		ResourceManager& _RM = ResourceManager::instance();

		return _RM.m_models;
	}

	/*Model* ResourceManager::ModelAsset(uint32_t index)
	{
		ResourceManager& _RM = ResourceManager::instance();

		if (index <= _RM.m_models.size())
			return _RM.m_models[index];
		else
			return NULL;
	}*/

    void ResourceManager::IncrementAssetRef(Asset* asset)
    {
        if (asset)
            asset->IncrementRefCount();
    }

    void ResourceManager::DecrementAssetRef(Asset* asset)
    {
		ResourceManager& _RM = ResourceManager::instance();

		if (asset->RefCount() <= 1) {

			UString fileName = asset->FileName();


			//THIS IS PERMABAD, DONT DO THIS
			Model* _isModel = static_cast<Model*>(asset);
			if (_isModel)
				_RM.m_models[fileName] = nullptr;

			delete asset;
			asset = nullptr;

			_RM.m_assetMap[fileName] = nullptr;
			
		}
			

        if (asset)
            asset->DecrementRefCount();
    }

	void ResourceManager::PrintLoaded()
	{
		ResourceManager& _RM = ResourceManager::instance();

		for (auto& asset : _RM.m_assetMap)
		{
			Asset* _asset = asset.second;
			if (_asset) {
				DebugPrintF(VTEXT("File: %s\n"), _asset->FileName().c_str());
				DebugPrintF(VTEXT("RefCount: %d\n"), _asset->RefCount());
			}
		}
	}
}
