#ifndef VIX_RESOURCEMANAGER_H
#define VIX_RESOURCEMANAGER_H

#include <vix_platform.h>
#include <vix_filemanager.h>

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
        Font
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


        static void     OpenResource(UString filePath);
        static void     OpenResource(UString fileName, ResourceType type);
        static File*    AccessResource(UString fileName, ResourceType type);

    private:
    };


}

#endif
