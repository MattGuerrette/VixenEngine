/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_dxrenderer.h>
#include <vix_dxprimitivecube.h>
#include <vix_dxvertexshader.h>
#include <vix_dxquad.h>
#include <vix_freeimage.h>
#include <vix_filemanager.h>
#include <vix_resourcemanager.h>

namespace Vixen {

    DXRenderer::DXRenderer()
    {
        m_HWND = NULL;
        m_camera2D = new DXCamera2D;
        m_spriteBatch = NULL;
        m_DefferedBuffers = new DXDefferedBuffers;
    }

    DXRenderer::~DXRenderer()
    {
        
    }

    void DXRenderer::VDeInitialize()
    {
        if(m_ImmediateContext)
            m_ImmediateContext->ClearState();
    
        ReleaseBuffers();
        ReleaseCOM(m_SwapChain);
        ReleaseCOM(m_ImmediateContext);
        ReleaseCOM(m_Device);

        delete m_spriteBatch;
        delete m_DefferedBuffers;
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

        RECT r;
        GetClientRect(m_HWND, &r);
        UINT width = r.right - r.left;
        UINT height = r.bottom - r.top;

        IDXGIDevice*  dxgiDevice = NULL;
        hr = m_Device->QueryInterface(__uuidof(IDXGIDevice),
            reinterpret_cast<void**>(&dxgiDevice));

        IDXGIAdapter* dxgiAdapter = NULL;
        dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
            reinterpret_cast<void**>(&dxgiAdapter));

        IDXGIFactory* dxgiFactory = NULL;
        dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
            reinterpret_cast<void**>(&dxgiFactory));


        ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
        m_SwapChainDesc.BufferDesc.Width = width;
        m_SwapChainDesc.BufferDesc.Height = height;
        m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        m_SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        m_SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        //multisampling (why not? actually..lets not)
        m_SwapChainDesc.SampleDesc.Count = 1;
        m_SwapChainDesc.SampleDesc.Quality = 0; //msaaQuality - 1;
        m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        m_SwapChainDesc.BufferCount = 1;
        m_SwapChainDesc.OutputWindow = m_HWND;
        m_SwapChainDesc.Windowed = true;
        m_SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        m_SwapChainDesc.Flags = 0;

        hr = dxgiFactory->CreateSwapChain(m_Device, &m_SwapChainDesc, &m_SwapChain);


        ReleaseCOM(dxgiDevice);
        ReleaseCOM(dxgiAdapter);
        ReleaseCOM(dxgiFactory);

        CreateBuffers(width, height);
       
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


        //Initialize deffered buffers
        m_DefferedBuffers->Initialize(m_Device, width, height);

        return true;
    }

    void DXRenderer::VInitializeSpriteBatch()
    {
        m_spriteBatch = new DXSpriteBatcher(m_Device, m_ImmediateContext);

		DXVertexShader* _vShader = (DXVertexShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_VS.hlsl"), ShaderType::VERTEX_SHADER);
		_vShader->IncrementRefCount();
        m_spriteBatch->SetVertexShader(_vShader);

		DXPixelShader* _pShader = (DXPixelShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_PS.hlsl"), ShaderType::PIXEL_SHADER);
		_pShader->IncrementRefCount();
        m_spriteBatch->SetPixelShader(_pShader);

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

        //Clear deffered buffers
        m_DefferedBuffers->ClearRenderTargets(m_ImmediateContext, m_clearColor);
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

    void DXRenderer::VResizeBuffers(uint32_t width, uint32_t height)
    {
        ReleaseBuffers();
        m_DefferedBuffers->ReleaseBuffers();

        m_SwapChain->ResizeBuffers(1, width, height, m_SwapChainDesc.BufferDesc.Format, 0);
        m_SwapChain->GetDesc(&m_SwapChainDesc);

        CreateBuffers(width, height);
        m_DefferedBuffers->Initialize(m_Device, width, height);

        OrthoRect _ortho;
        _ortho.left = 0.0f;
        _ortho.right = static_cast<float>(width);
        _ortho.top = 0.0f;
        _ortho.bottom = static_cast<float>(height);
        m_camera2D->VSetOrthoRHOffCenter(_ortho, 0.0f, 1.0f);
    }

    bool DXRenderer::CreateBuffers(uint32_t width, uint32_t height)
    {
        HRESULT hr;

        //CREATE RENDER TARGET VIEW
        ID3D11Texture2D* backBuffer;
        hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
            reinterpret_cast<void**>(&backBuffer));

        hr = m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView);

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


        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = dsd.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        hr = m_Device->CreateDepthStencilView(depthStencilBuffer, &descDSV, &m_DepthStencView);


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

        return true;
    }

    void DXRenderer::ReleaseBuffers()
    {
        //need to release existing buffers
        ReleaseCOM(m_RenderTargetView);
        ReleaseCOM(m_DepthStencView);
    }

    void DXRenderer::VRenderTexture2D(Texture* texture, const Vector2& position, const Rect& source)
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

	ICamera2D* DXRenderer::VCamera2D()
	{
		return m_camera2D;
	}

    void DXRenderer::VRenderText2D(Font* font, UString text, const Vector2& position)
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