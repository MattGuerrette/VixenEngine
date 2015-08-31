/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

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
#include <vix_dxquad.h>
#include <vix_freeimage.h>
#include <vix_filemanager.h>

namespace Vixen {

    DXRenderer::DXRenderer()
    {
        m_HWND = NULL;
        m_ConstantBuffer = nullptr;
        m_type = RendererType::DIRECTX;
        m_cube = nullptr;
        m_quad = nullptr;
        m_spriteBatch = new DXSpriteBatcher;
    }

    DXRenderer::~DXRenderer()
    {
        
    }

    void DXRenderer::VDeInitialize()
    {
        if(m_ImmediateContext)
            m_ImmediateContext->ClearState();
        ReleaseCOM(m_ConstantBuffer);
        ReleaseCOM(m_InputLayout);
        ReleaseCOM(m_VShader);
        ReleaseCOM(m_PShader);
        ReleaseCOM(m_RenderTargetView);
        ReleaseCOM(m_DepthStencView);
        ReleaseCOM(m_SwapChain);
        ReleaseCOM(m_ImmediateContext);
        ReleaseCOM(m_Device);

        delete m_cube;
        delete m_quad;
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
        vp.MaxDepth = 0;

        m_ImmediateContext->RSSetViewports(1, &vp);

        return true;
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

    void DXRenderer::VApplyRenderMode()
    {
        //NON APPLICABLE ATM
    }

    void DXRenderer::VApplyFaceCulling()
    {
        //NON APPLICABLE ATM
    }

    void DXRenderer::VApplyFaceWinding()
    {
        //NON APPLICABLE ATM
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

    void DXRenderer::VRenderTexture2D(ITexture* texture, const Transform& transform)
    {
        BatchInfo info;
        info.x = transform.X();
        info.y = transform.Y();
        info.sX = static_cast<float>(0);
        info.sY = static_cast<float>(0);
        info.sW = static_cast<float>(0);
        info.sH = static_cast<float>(0);
        info.originX = 0.0f;
        info.originY = 0.0f;
        info.scaleX = transform.ScaleX();
        info.scaleY = transform.ScaleY();
        info.rotation = Math::ToRadians(transform.RotZ());
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

    //
    // NOTE:
    //   JUST A TEST FUNCTION FOR RENDERING
    //
    //void DXRenderer::Render(float dt)
    //{
    //    m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, DirectX::Colors::CornflowerBlue);
    //    m_ImmediateContext->ClearDepthStencilView(m_DepthStencView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    //    
    //    static float rot = 0.0f;
    //    rot += dt;
    //   

    //    m_World = DirectX::XMMatrixScaling(m_texture->Width(), m_texture->Height(), 0.0f);

    //    //
    //    // Update variables
    //    //
    //    ConstantBuffer cb;
    //    cb.mWorld = DirectX::XMMatrixTranspose(m_World);
    //    //cb.mView = DirectX::XMMatrixTranspose(m_View);
    //    cb.mProjection = DirectX::XMMatrixTranspose(m_camera->Projection());
    //    m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &cb, 0, 0);

    //    m_quad->Render(m_ImmediateContext);
    //    
    //    
    //    m_SwapChain->Present(0, 0);
    //}

}