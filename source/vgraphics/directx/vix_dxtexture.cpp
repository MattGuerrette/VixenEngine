#include <vix_dxtexture.h>

namespace Vixen {

    DXTexture::DXTexture()
    {
        m_resourceView = nullptr;
        m_sampleState = nullptr;
        m_width = 0.0f;
        m_height = 0.0f;
    }

    DXTexture::~DXTexture()
    {
        ReleaseCOM(m_resourceView);
        ReleaseCOM(m_sampleState);
    }

    bool DXTexture::LoadFromBitmap(ID3D11Device* device, FREEIMAGE_BMP* bitmap)
    {
        HRESULT hr;

        m_width = bitmap->header.width;
        m_height = bitmap->header.height;

        //We are now going to create a DX11 Texture
        D3D11_TEXTURE2D_DESC desc;
        desc.Width = static_cast<UINT>(bitmap->header.width);
        desc.Height = static_cast<UINT>(bitmap->header.height);
        desc.MipLevels = 1; //will autogenerate
        desc.ArraySize = 1;
        desc.Format = FromBPP(bitmap->bpp);
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.MiscFlags = 0;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subTexData;
        ZeroMemory(&subTexData, sizeof(D3D11_SUBRESOURCE_DATA));
        subTexData.pSysMem = bitmap->data;
        subTexData.SysMemPitch = FreeImage_GetPitch(bitmap->bitmap);


        ID3D11Texture2D* tex;
        hr = device->CreateTexture2D(&desc, &subTexData, &tex);
        if (FAILED(hr))
        {
            DebugPrintF(VTEXT("FAILED TO CREATE TEXTURE"));
            return false;
        }
        
        D3D11_SHADER_RESOURCE_VIEW_DESC svd;
        ZeroMemory(&svd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
        svd.Format = FromBPP(bitmap->bpp);
        svd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        svd.Texture2D.MipLevels = desc.MipLevels;

        hr = device->CreateShaderResourceView(tex, &svd, &m_resourceView);
        if (FAILED(hr))
            return false;

        //FREE ID3D11Texture2D*
        ReleaseCOM(tex);

        // Create the sample state
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
        hr = device->CreateSamplerState(&sampDesc, &m_sampleState);
        if (FAILED(hr))
            return false;


        return true;
    }

    ID3D11ShaderResourceView* DXTexture::ResourceView()
    {
        return m_resourceView;
    }

    ID3D11SamplerState* DXTexture::SampleState()
    {
        return m_sampleState;
    }

    float DXTexture::Width()
    {
        return m_width;
    }

    float DXTexture::Height()
    {
        return m_height;
    }

    DXGI_FORMAT DXTexture::FromBPP(size_t bpp)
    {
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

        switch (bpp)
        {
        case 32:
            format = DXGI_FORMAT_B8G8R8A8_UNORM;
            break;
        }

        return format;
    }
}