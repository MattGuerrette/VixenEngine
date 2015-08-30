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
        UString assetPath = PathManager::AssetPath() + VTEXT("Shaders/");

        assetPath += filePath;
        assetPath = os_path(assetPath);

        File* file = FileManager::OpenFile(assetPath);
        if (file)
        {
            //Create Renderer Specific texture type
            ResourceManager& _RM = ResourceManager::instance();

            if (_RM.m_resourceLoader)
                return _RM.m_resourceLoader->LoadShader(file, type);

        }

        return NULL;
    }

    //Shader* ResourceManager::Open

    //void ResourceManager::OpenResource(UString fileName, ResourceType type)
    //{
    //    UString assetPath = PathManager::AssetPath();
    //    switch(type)
    //    {
    //        case ResourceType::Texture:
    //        {
    //            //Append Texutes to asset path
    //            assetPath += VTEXT("Textures/");
    //        } break;

    //        case ResourceType::Model:
    //        {
    //            assetPath += VTEXT("Models/");
    //        } break;

    //        case ResourceType::Font:
    //        {
    //            assetPath += VTEXT("Fonts/");
    //        } break;

    //        case ResourceType::Shader:
    //        {
    //            assetPath += VTEXT("Shaders/");
    //        } break;
    //    }

    //    assetPath += fileName;

    //    //Load file
    //    FileManager::OpenFile(assetPath);
    //}

    //File* ResourceManager::AccessResource(UString fileName, ResourceType type)
    //{
    //    UString assetPath = PathManager::AssetPath();
    //    switch(type)
    //    {
    //        case ResourceType::Texture:
    //        {
    //            //Append Texutes to asset path
    //            assetPath += VTEXT("Textures/");
    //        } break;

    //        case ResourceType::Model:
    //        {
    //            assetPath += VTEXT("Models/");
    //        } break;

    //        case ResourceType::Font:
    //        {
    //            assetPath += VTEXT("Fonts/");
    //        } break;
    //    }

    //    assetPath += fileName;

    //    //Return file
    //    return FileManager::AccessFile(assetPath);
    //}

}
