#ifndef VIX_RESOURCELOADER_H
#define VIX_RESOURCELOADER_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_texture.h>
#include <vix_shader.h>

namespace Vixen {

    class VIX_API IResourceLoader
    {
    public:
        virtual ~IResourceLoader() { }

        virtual ITexture* LoadTexture(File* file) = 0;
        virtual IShader*  LoadShader(File* file, ShaderType type) = 0;
    };

}

#endif
