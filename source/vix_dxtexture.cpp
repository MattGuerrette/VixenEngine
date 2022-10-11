/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <vix_dxtexture.h>
#include <vix_resourcemanager.h>

namespace Vixen {

    DXTexture::DXTexture(ID3D11Device* device, ID3D11DeviceContext* context)
        : Texture()
    {
        m_device = device;
        m_context = context;

        m_resourceView = nullptr;
        m_sampleState = nullptr;
        m_width = 0;
        m_height = 0;
    }

    DXTexture::~DXTexture()
    {
        ReleaseCOM(m_resourceView);
        ReleaseCOM(m_sampleState);
    }

    bool DXTexture::VInitFromFile(File* file)
    {
        if (!file)
            return false;

        FREEIMAGE_BMP* bitmap = FREEIMAGE_LoadImage(file);
        if (bitmap)
        {
            return VInitFromBMP(bitmap);
        }

        return false;
    }

    bool DXTexture::VInitFromBMP(FREEIMAGE_BMP* bmp)
    {
        HRESULT hr;

        m_width = bmp->header.width;
        m_height = bmp->header.height;

        //We are now going to create a DX11 Texture
        D3D11_TEXTURE2D_DESC desc;
        desc.Width = static_cast<UINT>(bmp->header.width);
        desc.Height = static_cast<UINT>(bmp->header.height);
        desc.MipLevels = 1; //will autogenerate
        desc.ArraySize = 1;
        desc.Format = FromBPP(bmp->bpp);
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
        desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subTexData;
        ZeroMemory(&subTexData, sizeof(D3D11_SUBRESOURCE_DATA));
        subTexData.pSysMem = bmp->data;
        subTexData.SysMemPitch = FreeImage_GetPitch(bmp->bitmap);


        ID3D11Texture2D* tex;
        hr = m_device->CreateTexture2D(&desc, &subTexData, &tex);
        if (FAILED(hr))
        {
            DebugPrintF(VTEXT("FAILED TO CREATE TEXTURE"));
            return false;
        }

        D3D11_SHADER_RESOURCE_VIEW_DESC svd;
        ZeroMemory(&svd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
        svd.Format = FromBPP(bmp->bpp);
        svd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        svd.Texture2D.MipLevels = desc.MipLevels;

        hr = m_device->CreateShaderResourceView(tex, &svd, &m_resourceView);
        if (FAILED(hr))
            return false;

        m_context->GenerateMips(m_resourceView);

        //FREE ID3D11Texture2D*
        ReleaseCOM(tex);

        // Create the sample state
        D3D11_SAMPLER_DESC sampDesc;
        ZeroMemory(&sampDesc, sizeof(sampDesc));
        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
        hr = m_device->CreateSamplerState(&sampDesc, &m_sampleState);
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

    size_t DXTexture::VGetWidth() const
    {
        return m_width;
    }

    size_t DXTexture::VGetHeight() const
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
