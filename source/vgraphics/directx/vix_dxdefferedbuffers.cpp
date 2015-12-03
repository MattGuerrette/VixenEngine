#include <vix_dxdefferedbuffers.h>

namespace Vixen {
    
    DXDefferedBuffers::DXDefferedBuffers()
    {
        //Init all COM objects pointers to NULL
        for (int i = 0; i < BUFFER_COUNT; i++)
        {
            m_RenderTargetTextures[i] = NULL;
            m_RenderTargetViews[i] = NULL;
            m_ShaderResourceViews[i] = NULL;
        }
        m_DepthStencilBuffer = NULL;
        m_DepthStencilView = NULL;
    }

    DXDefferedBuffers::~DXDefferedBuffers()
    {
        ReleaseBuffers();
    }

    void DXDefferedBuffers::ReleaseBuffers()
    {
        //Release COM Objects
        for (int i = 0; i < BUFFER_COUNT; i++)
        {
            if (m_RenderTargetTextures[i])
                ReleaseCOM(m_RenderTargetTextures[i]);
            if (m_RenderTargetViews[i])
                ReleaseCOM(m_RenderTargetViews[i]);
            if (m_ShaderResourceViews[i])
                ReleaseCOM(m_ShaderResourceViews[i]);
        }

        if (m_DepthStencilView)
            ReleaseCOM(m_DepthStencilView);
        if (m_DepthStencilBuffer)
            ReleaseCOM(m_DepthStencilBuffer);
    }

    ID3D11ShaderResourceView* DXDefferedBuffers::GetShaderResourceView(int index)
    {
        if (index < 0 || index >= BUFFER_COUNT)
            return NULL;

        return m_ShaderResourceViews[index];
    }

    bool DXDefferedBuffers::Initialize(ID3D11Device* device, uint32_t width, uint32_t height)
    {
        HRESULT hr = S_OK;

        //Setup Render Target Texture Desc

        D3D11_TEXTURE2D_DESC texDesc;
        ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));
        texDesc.Width = width;
        texDesc.Height = height;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D11_USAGE_DEFAULT;
        texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        texDesc.CPUAccessFlags = 0;
        texDesc.MiscFlags = 0;

        //Create render target textures
        int i = 0;
        for (i = 0; i < BUFFER_COUNT; i++)
        {
            hr = device->CreateTexture2D(&texDesc, NULL, &m_RenderTargetTextures[i]);
            if (FAILED(hr))
                return false;
        }

        //Setup Render Target View Desc
        D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
        rtvDesc.Format = texDesc.Format;
        rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        rtvDesc.Texture2D.MipSlice = 0;

        //Create render target views
        for (i = 0; i < BUFFER_COUNT; i++)
        {
            hr = device->CreateRenderTargetView(m_RenderTargetTextures[i], &rtvDesc, &m_RenderTargetViews[i]);
            if (FAILED(hr))
                return false;
        }

        //Setup Shader Resource View Desc
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        srvDesc.Format = texDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = 1;

        //Create shader resource views
        for (i = 0; i < BUFFER_COUNT; i++)
        {
            hr = device->CreateShaderResourceView(m_RenderTargetTextures[i], &srvDesc, &m_ShaderResourceViews[i]);
            if (FAILED(hr))
                return false;
        }


        //CREATE DEPTH/STENCIL VIEW
        D3D11_TEXTURE2D_DESC dsd;
        dsd.Width = width;
        dsd.Height = height;
        dsd.MipLevels = 1;
        dsd.ArraySize = 1;
        dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //D24 S8                     
        dsd.SampleDesc.Count = 1; 
        dsd.SampleDesc.Quality = 0;
        dsd.Usage = D3D11_USAGE_DEFAULT;
        dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        dsd.CPUAccessFlags = 0;
        dsd.MiscFlags = 0;

        hr = device->CreateTexture2D(&dsd, 0, &m_DepthStencilBuffer);
        if (FAILED(hr))
            return false;

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = dsd.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;

        hr = device->CreateDepthStencilView(m_DepthStencilBuffer, &descDSV, &m_DepthStencilView);
        if (FAILED(hr))
            return false;

        return true;
    }

    void DXDefferedBuffers::BindRenderTargets(ID3D11DeviceContext* context)
    {
        //Bind render target view array and depth stencil buffer
        context->OMSetRenderTargets(3, m_RenderTargetViews, m_DepthStencilView);
    }

	void DXDefferedBuffers::BindRenderTarget(uint32_t index, ID3D11DeviceContext* context)
	{

		ID3D11RenderTargetView* view = m_RenderTargetViews[3];
		ID3D11RenderTargetView* views[4] = { nullptr, nullptr, nullptr, view };
		context->OMSetRenderTargets(1, views, m_DepthStencilView);
	}

    void DXDefferedBuffers::UnbindRenderTargets(ID3D11DeviceContext* context)
    {
        context->OMSetRenderTargets(BUFFER_COUNT, NULL, NULL);
    }

    void DXDefferedBuffers::ClearRenderTargets(ID3D11DeviceContext* context, DirectX::XMVECTORF32 clearColor)
    {
        for (int i = 0; i < BUFFER_COUNT; i++)
            context->ClearRenderTargetView(m_RenderTargetViews[i], clearColor);

        context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

	void DXDefferedBuffers::ClearDepthStencil(ID3D11DeviceContext* context)
	{
		context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}