/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

namespace Vixen {

    ResourceManager::~ResourceManager()
    {

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

        ITexture* _texture = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
                _texture =_RM.m_resourceLoader->LoadTexture(file);

                FileManager::CloseFile(file);
            }
        }

        return _texture;
    }

    IShader* ResourceManager::OpenShader(UString filePath, ShaderType type)
    {
        UString assetPath = PathManager::ShaderPath();

        assetPath += filePath;
        assetPath = os_path(assetPath);

        IShader* _shader = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
               _shader = _RM.m_resourceLoader->LoadShader(file, type);

               FileManager::CloseFile(assetPath);
            }
        }

        return _shader;
    }

    IModel* ResourceManager::OpenModel(UString filePath)
    {
        UString assetPath = PathManager::ModelPath();

        assetPath += filePath;
        assetPath = os_path(assetPath);

        IModel* _model = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific model type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
                //Need to load a model object into memory
                _model = _RM.m_resourceLoader->LoadModel(file);

                FileManager::CloseFile(assetPath);
            }
        }

        return _model;
    }

    IFont* ResourceManager::OpenFont(UString filePath)
    {
        UString assetPath = PathManager::AssetPath() + VTEXT("Fonts/");

        assetPath += filePath;
        assetPath = os_path(assetPath);

        IFont* _font = NULL;

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific model type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
            {
                //Need to load a font object into memory
                _font = _RM.m_resourceLoader->LoadFont(file);

                FileManager::CloseFile(assetPath);
            }
        }

        return _font;
    }
}
