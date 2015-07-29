#include <vix_dxrenderer.h>
#include <vix_dxprimitivecube.h>

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

namespace Vixen {

    DXRenderer::DXRenderer(HWND hwnd)
    {
        m_HWND = hwnd;
        m_ConstantBuffer = nullptr;
        m_type = RendererType::DIRECTX;
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
        hr = m_Device->CreateDepthStencilView(depthStencilBuffer, 0, &m_DepthStencView);
        if (FAILED(hr))
            return false;

        ReleaseCOM(depthStencilBuffer);

        m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);

        //Create the VIEWPORT structure
        //
        // For now I will just grab the entire size of the window

        D3D11_VIEWPORT vp;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;
        vp.Width = static_cast<float>(width);
        vp.Height = static_cast<float>(height);
        vp.MinDepth = 0;
        vp.MaxDepth = 0;

        m_ImmediateContext->RSSetViewports(1, &vp);

        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        hr = CompileShaderFromFile(L"test.fx", "VS", "vs_4_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        hr = m_Device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_VShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };
        UINT numElements = ARRAYSIZE(layout);

        // Create the input layout
        hr = m_Device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
            pVSBlob->GetBufferSize(), &m_InputLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Set the input layout
        m_ImmediateContext->IASetInputLayout(m_InputLayout);

        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        hr = CompileShaderFromFile(L"test.fx", "PS", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = m_Device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_PShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Set primitive topology
        m_ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        D3D11_BUFFER_DESC cbd;
        ZeroMemory(&cbd, sizeof(cbd));
        cbd.Usage = D3D11_USAGE_DEFAULT;
        cbd.ByteWidth = sizeof(ConstantBuffer);
        cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbd.CPUAccessFlags = 0;
        hr = m_Device->CreateBuffer(&cbd, NULL, &m_ConstantBuffer);
        if (FAILED(hr))
            return hr;

        // Initialize the world matrix
        m_World = DirectX::XMMatrixIdentity();

        // Initialize the view matrix
        DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
        DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        m_View = DirectX::XMMatrixLookAtLH(Eye, At, Up);

        // Initialize the projection matrix
        m_Projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f);
        

        m_cube = new DXPrimitiveCube;
        m_cube->Initialize(m_Device);
        m_cube->SetPixelShader(m_PShader);
        m_cube->SetVertexShader(m_VShader);
        m_cube->SetConstantBuffer(m_ConstantBuffer);
        

        return true;
    }

    //
    // NOTE:
    //   JUST A TEST FUNCTION FOR RENDERING
    //
    void DXRenderer::VRender()
    {
        m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, DirectX::Colors::CornflowerBlue);
        m_ImmediateContext->ClearDepthStencilView(m_DepthStencView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        
        static float rot = 0.0f;
        rot += 0.0001f;

        m_World = DirectX::XMMatrixRotationY(rot);

        //
        // Update variables
        //
        ConstantBuffer cb;
        cb.mWorld = DirectX::XMMatrixTranspose(m_World);
        cb.mView = DirectX::XMMatrixTranspose(m_View);
        cb.mProjection = DirectX::XMMatrixTranspose(m_Projection);
        m_ImmediateContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &cb, 0, 0);

        m_cube->Render(m_ImmediateContext);
        
      /*  m_ImmediateContext->VSSetShader(m_VShader, nullptr, 0);
        m_ImmediateContext->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
        m_ImmediateContext->PSSetShader(m_PShader, nullptr, 0);
        m_ImmediateContext->Draw(3, 0);*/
        
        m_SwapChain->Present(0, 0);
    }

}