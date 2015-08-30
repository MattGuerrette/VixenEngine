#ifndef VIX_DXTEXTURE_H
#define VIX_DXTEXTURE_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_freeimage.h>
#include <vix_texture.h>

namespace Vixen {

    class VIX_API DXTexture : public ITexture
    {
    public:
        DXTexture(ID3D11Device* device);

        ~DXTexture();

        bool InitFromFile(File* file);
        bool InitFromBMP(FREEIMAGE_BMP* bmp);

        ID3D11ShaderResourceView*  ResourceView();
        ID3D11SamplerState*        SampleState();
        float                      Width();
        float                      Height();

    private:
        ID3D11Device*              m_device;
        ID3D11ShaderResourceView*  m_resourceView;
        ID3D11SamplerState*        m_sampleState;

    private:
        static DXGI_FORMAT FromBPP(size_t bpp);
    };

}

#endif
