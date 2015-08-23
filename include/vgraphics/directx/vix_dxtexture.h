#ifndef VIX_DXTEXTURE_H
#define VIX_DXTEXTURE_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_freeimage.h>

namespace Vixen {

    class VIX_API DXTexture
    {
    public:
        DXTexture();

        ~DXTexture();

        bool LoadFromBitmap(ID3D11Device* device, FREEIMAGE_BMP* bitmap);

        ID3D11ShaderResourceView*  ResourceView();
        ID3D11SamplerState*        SampleState();
        float                      Width();
        float                      Height();

    private:
        ID3D11ShaderResourceView*  m_resourceView;
        ID3D11SamplerState*        m_sampleState;
        float                      m_width;
        float                      m_height;

    private:
        static DXGI_FORMAT FromBPP(size_t bpp);
    };

}

#endif
