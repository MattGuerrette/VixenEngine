/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vix_dxrenderer.h>
#include <vix_dxprimitivecube.h>
#include <vix_dxquad.h>
#include <vix_freeimage.h>
#include <vix_filemanager.h>
#include <vix_resourcemanager.h>

namespace Vixen {

    DXRenderer::DXRenderer()
    {
        m_HWND = NULL;
        m_camera2D = new DXCamera2D;
    }

    DXRenderer::~DXRenderer()
    {

    }

    void DXRenderer::VDeInitialize()
    {
        if(m_ImmediateContext)
            m_ImmediateContext->ClearState();

        ReleaseCOM(m_RenderTargetView);
        ReleaseCOM(m_DepthStencView);
        ReleaseCOM(m_SwapChain);
        ReleaseCOM(m_ImmediateContext);
        ReleaseCOM(m_Device);

        delete m_spriteBatch;
    }

    bool DXRenderer::VInitialize()
    {
        HRESULT hr = S_OK;

        //Need to initialize DirectX 11.0 device

        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        //Build Driver Type List
        D3D_DRIVER_TYPE drivers[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_REFERENCE,
            D3D_DRIVER_TYPE_WARP
        };
        size_t numDrivers = ARRAYSIZE(drivers);

        //Build Feature Level List
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0
        };
        size_t numLevels = ARRAYSIZE(featureLevels);

        for (size_t i = 0; i < numDrivers; i++)
        {
            //Create device against each device type
            //then we return out.

            hr = D3D11CreateDevice(NULL, drivers[i], NULL, createDeviceFlags,
                featureLevels, numLevels, D3D11_SDK_VERSION, &m_Device, &m_FeatureLevel, &m_ImmediateContext);

            if (SUCCEEDED(hr))
                break;
        }
        if (FAILED(hr))
            return false;



        //Check multisampling support.
        //NOTE:
        //
        // This will eventually take value from engine config file.
        UINT msaaQuality;
        hr = m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality);

        //Need to grab the same IDXGIFactory object that was used to create
        //the device

        IDXGIDevice*  dxgiDevice = NULL;
        hr = m_Device->QueryInterface(__uuidof(IDXGIDevice),
            reinterpret_cast<void**>(&dxgiDevice));
        if (FAILED(hr))
            return false;

        IDXGIAdapter* dxgiAdapter = NULL;
        dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
            reinterpret_cast<void**>(&dxgiAdapter));
        if (FAILED(hr))
            return false;

        IDXGIFactory* dxgiFactory = NULL;
        dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
            reinterpret_cast<void**>(&dxgiFactory));
        if (FAILED(hr))
            return false;

        RECT r;
        GetClientRect(m_HWND, &r);
        UINT width = r.right - r.left;
        UINT height = r.bottom - r.top;

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        //multisampling (why not? actually..lets not)
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0; //msaaQuality - 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;
        sd.OutputWindow = m_HWND;
        sd.Windowed = true;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags = 0;

        hr = dxgiFactory->CreateSwapChain(m_Device, &sd, &m_SwapChain);
        if (FAILED(hr))
            return false;

        ReleaseCOM(dxgiDevice);
        ReleaseCOM(dxgiAdapter);
        ReleaseCOM(dxgiFactory);

        //CREATE RENDER TARGET VIEW
        ID3D11Texture2D* backBuffer;
        hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
            reinterpret_cast<void**>(&backBuffer));
        if (FAILED(hr))
            return false;
        hr = m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView);
        if (FAILED(hr))
            return false;
        ReleaseCOM(backBuffer);


        //CREATE DEPTH/STENCIL VIEW
        D3D11_TEXTURE2D_DESC dsd;
        dsd.Width = width;
        dsd.Height = height;
        dsd.MipLevels = 1;
        dsd.ArraySize = 1;
        dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //D24 S8

        //MSAA (why not?)
        dsd.SampleDesc.Count = 1; //4;
        dsd.SampleDesc.Quality = 0; //msaaQuality - 1;
        dsd.Usage = D3D11_USAGE_DEFAULT;
        dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        dsd.CPUAccessFlags = 0;
        dsd.MiscFlags = 0;

        ID3D11Texture2D* depthStencilBuffer;
        hr = m_Device->CreateTexture2D(&dsd, 0, &depthStencilBuffer);
        if (FAILED(hr))
            return false;

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = dsd.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = m_Device->CreateDepthStencilView(depthStencilBuffer, &descDSV, &m_DepthStencView);
        if (FAILED(hr))
            return false;

        ReleaseCOM(depthStencilBuffer);

        m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);


        D3D11_VIEWPORT vp;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;
        vp.Width = static_cast<float>(width);
        vp.Height = static_cast<float>(height);
        vp.MinDepth = 0;
        vp.MaxDepth = 1;

        m_ImmediateContext->RSSetViewports(1, &vp);


        OrthoRect _ortho;
        _ortho.left = 0.0f;
        _ortho.right = static_cast<float>(width);
        _ortho.top = 0.0f;
        _ortho.bottom = static_cast<float>(height);
        m_camera2D->VSetOrthoRHOffCenter(_ortho, 0.0f, 1.0f);
  


        D3D11_BLEND_DESC blendDesc;
        ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        blendDesc.RenderTarget[0].BlendEnable = true;
        blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

        blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
        blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        ID3D11BlendState* state;
        m_Device->CreateBlendState(&blendDesc, &state);
        m_ImmediateContext->OMSetBlendState(state, NULL, 0xfffffffff);

        ReleaseCOM(state);




        return true;
    }

    void DXRenderer::VInitializeSpriteBatch()
    {
        m_spriteBatch = new DXSpriteBatcher(m_Device, m_ImmediateContext);
        m_spriteBatch->SetVertexShader((DXVertexShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_VS.hlsl"), ShaderType::VERTEX_SHADER));
        m_spriteBatch->SetPixelShader((DXPixelShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_PS.hlsl"), ShaderType::PIXEL_SHADER));

        m_spriteBatch->SetCamera(m_camera2D);
    }

    void DXRenderer::VSetClearColor(const Color& c)
    {
        DirectX::XMVECTORF32 vec = { c.r, c.g, c.b, c.a };

        m_clearColor = vec;
    }

    void DXRenderer::VClearBuffer(ClearArgs args)
    {
        m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, m_clearColor);
        m_ImmediateContext->ClearDepthStencilView(m_DepthStencView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    void DXRenderer::VAttachNativeHandle(void* handle)
    {
        m_HWND = (HWND)handle;
    }

    void DXRenderer::VSwapBuffers()
    {
        m_SwapChain->Present(0, 0);
    }

    ID3D11Device* DXRenderer::Device()
    {
        return m_Device;
    }

    ID3D11DeviceContext* DXRenderer::DeviceContext()
    {
        return m_ImmediateContext;
    }

    void DXRenderer::VRenderTexture2D(ITexture* texture, const Vector2& position, const Rect& source)
    {
        BatchInfo info;
        info.x = position.x;
        info.y = position.y;
        info.sX = static_cast<float>(source.x);
        info.sY = static_cast<float>(source.y);
        info.sW = static_cast<float>(source.w);
        info.sH = static_cast<float>(source.h);
        info.originX = 16.f;
        info.originY = 16.f;
        info.scaleX = 1.0f;
        info.scaleY = 1.0f;
		info.rotation = 0.0f;
        info.r = 0.0f;
        info.g = 0.0f;
        info.b = 0.0f;
        info.a = 0.0f;
        info.alpha = 1.0f;
        info.depth = 0.0f;

        m_spriteBatch->Begin(BatchSortMode::IMMEDITATE);
        m_spriteBatch->Render(texture, info);
        m_spriteBatch->End();
    }

    void DXRenderer::VRenderText2D(IFont* font, UString text, const Vector2& position)
    {
        m_spriteBatch->Begin(BatchSortMode::IMMEDITATE);

		float x = position.x;
		if (position.x == -1) {
			float midX = static_cast<float>((1280 - font->VBounds(text).w) / 2);
			x = midX;
		}
		float y = position.y;
		if (position.y == -1) {
			float midY = static_cast<float>((720 - font->VBounds(text).h) / 2);
			y = midY;
		}

		float dx = x;
		float dy = y;
        for (UChar &c : text)
        {
            if (c == '\n')
            {
                dx = x;
                dy += font->VLineHeight();
                continue;
            }

            FontChar fc;
            if (font->VFindChar(c, fc))
            {
                BatchInfo info;
                info.x = dx + fc.xOffset;
                info.y = dy + fc.yOffset;
                info.sX = (float)fc.x;
                info.sY = (float)fc.y;
                info.sW = (float)fc.width;
                info.sH = (float)fc.height;
                info.originX = 0;
                info.originY = 0;
                info.scaleX = 1;
                info.scaleY = 1;
                info.rotation = 0.0f;
                info.depth = 1;


                m_spriteBatch->Render(font->VPageTexture(fc.page), info);

                dx += fc.xAdvance;
            }
        }

        m_spriteBatch->End();
    }

    DXSpriteBatcher* DXRenderer::SpriteBatch()
    {
        return m_spriteBatch;
    }
}
