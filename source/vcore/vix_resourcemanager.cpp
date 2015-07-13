#include <vix_resourcemanager.h>
#include <vix_pathmanager.h>

namespace Vixen {

    ResourceManager::~ResourceManager()
    {

    }

    void ResourceManager::OpenResource(UString filePath)
    {

    }

    void ResourceManager::OpenResource(UString fileName, ResourceType type)
    {
        UString assetPath = PathManager::instance().AssetPath();
        switch(type)
        {
            case ResourceType::Texture:
            {
                //Append Texutes to asset path
                assetPath += VTEXT("Textures/");
            } break;

            case ResourceType::Model:
            {
                assetPath += VTEXT("Models/");
            } break;

            case ResourceType::Font:
            {
                assetPath += VTEXT("Fonts/");
            } break;
        }

        assetPath += fileName;

        //Load file
        FileManager::instance().OpenFile(assetPath);
    }

    File* ResourceManager::AccessResource(UString fileName, ResourceType type)
    {
        UString assetPath = PathManager::instance().AssetPath();
        switch(type)
        {
            case ResourceType::Texture:
            {
                //Append Texutes to asset path
                assetPath += VTEXT("Textures/");
            } break;

            case ResourceType::Model:
            {
                assetPath += VTEXT("Models/");
            } break;

            case ResourceType::Font:
            {
                assetPath += VTEXT("Fonts/");
            } break;
        }

        assetPath += fileName;

        //Return file
        return FileManager::instance().AccessFile(assetPath);
    }

}
