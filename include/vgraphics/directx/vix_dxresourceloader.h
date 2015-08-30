#ifndef VIX_DXRESOURCELOADER_H
#define VIX_DXRESOURCELOADER_H

#include <vix_platform.h>
#include <vix_resourceloader.h>

namespace Vixen {

    class DXRenderer;

    class VIX_API DXResourceLoader : public IResourceLoader
    {
    public:
        DXResourceLoader(DXRenderer* renderer);

        ~DXResourceLoader();

        ITexture* LoadTexture(File* file) override;

        IShader*  LoadShader(File* file, ShaderType type) override;

    private:
        DXRenderer* m_renderer;
    };

}

#endif
