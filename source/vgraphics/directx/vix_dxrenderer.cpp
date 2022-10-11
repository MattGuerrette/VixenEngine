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

#include <vix_dxrenderer.h>
#include <vix_dxprimitivecube.h>
#include <vix_dxvertexshader.h>
#include <vix_dxquad.h>
#include <vix_dxmodel.h>
#include <vix_freeimage.h>
#include <vix_filemanager.h>
#include <vix_resourcemanager.h>
#include <vix_mathfunctions.h>
#include <iterator>

namespace Vixen {

	DXRenderer::DXRenderer()
	{
		m_HWND = NULL;
		m_camera2D = new DXCamera2D;
		m_spriteBatch = NULL;
		m_DefferedBuffers = new DXDefferedBuffers;

		m_pointLightBuffer = NULL;
		m_spotLightBuffer = NULL;

        m_FinalPassVS = NULL;
        m_FinalPassPS = NULL;
        m_FinalPassSS = NULL;
	}

	DXRenderer::~DXRenderer()
	{

	}

	void DXRenderer::VDeInitialize()
	{
		if (m_ImmediateContext)
			m_ImmediateContext->ClearState();

		ReleaseBuffers();
		ReleaseCOM(m_SwapChain);
		ReleaseCOM(m_ImmediateContext);
		ReleaseCOM(m_Device);
       
		delete m_spriteBatch;
		delete m_DefferedBuffers;
        delete m_pointLightBuffer;
		delete m_spotLightBuffer;

        //////////////////////////////////////////
        // Release Final Pass Variables
        //////////////////////////////////////////
        ResourceManager::DecrementAssetRef(m_FinalPassVS);
        ResourceManager::DecrementAssetRef(m_FinalPassPS);
        ReleaseCOM(m_FinalPassSS);
		ReleaseCOM(m_lightBlendState);
		ReleaseCOM(m_lightDSState);

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

		//Initialize deffered buffers
	    m_DefferedBuffers->Initialize(m_Device, width, height);

		//m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);
		m_DefferedBuffers->BindRenderTargets(m_ImmediateContext);

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
		/*blendDesc.AlphaToCoverageEnable = true;
		blendDesc.IndependentBlendEnable = true;*/
		for (int i = 0; i < 8; i++)
		{
			//blendDesc.RenderTarget[i].BlendEnable = true;
			//blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
			//blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_ZERO;
			//blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;

			///*blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
			//blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
			//blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;*/
			//blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[i].BlendEnable = true;
			blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		hr = m_Device->CreateBlendState(&blendDesc, &m_lightBlendState);
		if (FAILED(hr))
			return false;

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
		hr = m_Device->CreateSamplerState(&sampDesc, &m_FinalPassSS);


		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.StencilEnable = FALSE;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		m_Device->CreateDepthStencilState(&depthStencilDesc, &m_lightDSState);

        m_pointLightBuffer = new DXLightBuffer(256, sizeof(PointLight), m_Device, m_ImmediateContext);
		m_spotLightBuffer = new DXLightBuffer(256, sizeof(SpotLight), m_Device, m_ImmediateContext);
		return true;
	}

	void DXRenderer::VInitializeSpriteBatch()
	{
		m_spriteBatch = new DXSpriteBatcher(m_Device, m_ImmediateContext);

		DXVertexShader* vShader = (DXVertexShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_VS.hlsl"), ShaderType::VERTEX_SHADER);
		vShader->IncrementRefCount();
		m_spriteBatch->SetVertexShader(vShader);

		DXPixelShader* pShader = (DXPixelShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_PS.hlsl"), ShaderType::PIXEL_SHADER);
		pShader->IncrementRefCount();
		m_spriteBatch->SetPixelShader(pShader);

		m_spriteBatch->SetCamera(m_camera2D);


		m_FinalPassVS = (DXVertexShader*)ResourceManager::OpenShader(VTEXT("BackBufferTarget_Deferred_VS.hlsl"), ShaderType::VERTEX_SHADER);
		m_FinalPassVS->IncrementRefCount();
		m_FinalPassPS = (DXPixelShader*)ResourceManager::OpenShader(VTEXT("BackBufferTarget_Deferred_PS.hlsl"), ShaderType::PIXEL_SHADER);
		m_FinalPassPS->IncrementRefCount();
	}

	void DXRenderer::VSetClearColor(const Color& c)
	{
		DirectX::XMVECTORF32 vec = { c.r, c.g, c.b, c.a };

		m_clearColor = vec;
	}

	void DXRenderer::VClearBuffer(ClearArgs args)
	{
		//Clear deffered buffers
		m_DefferedBuffers->ClearRenderTargets(m_ImmediateContext, m_clearColor);

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

	void DXRenderer::VResizeBuffers(uint32_t width, uint32_t height)
	{
		ReleaseBuffers();
		m_DefferedBuffers->ReleaseBuffers();

		m_SwapChain->ResizeBuffers(1, width, height, m_SwapChainDesc.BufferDesc.Format, 0);
		m_SwapChain->GetDesc(&m_SwapChainDesc);

		CreateBuffers(width, height);
		m_DefferedBuffers->Initialize(m_Device, width, height);


		//m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);



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



		return true;
	}

	void DXRenderer::VLightPass(ICamera3D* camera, Model* model, std::vector<PointLight*>& lights)
	{
		std::vector<PointLight> data;
		std::transform(lights.begin(), lights.end(), std::back_inserter(data),
			[](PointLight* light) { return *light; });

		if (data.size() <= 0) return;

		m_pointLightBuffer->VUpdateSubData(0, sizeof(PointLight), data.size(), &data[0]);
		//this->VLightPass(camera, model);

		using namespace DirectX;

		//m_DefferedBuffers->ClearDepthStencil(m_ImmediateContext);
		//m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);
		m_DefferedBuffers->BindRenderTarget(3, m_ImmediateContext);

		float blendFactor[4];


		// Setup the blend factor.
		blendFactor[0] = 1.0f;
		blendFactor[1] = 1.0f;
		blendFactor[2] = 1.0f;
		blendFactor[3] = 1.0f;

		m_ImmediateContext->OMSetBlendState(m_lightBlendState, blendFactor, 0xffffffff);
		m_ImmediateContext->OMSetDepthStencilState(m_lightDSState, 0);
		//->OMSetBlendState(m_lightBlendState, NULL, 0xfffffffff);

		DXModel* _model = (DXModel*)model;

		_model->GetMaterial()->GetVertexShader()->VSetShaderResourceView("LightBuffer", m_pointLightBuffer->GetSRV());
		_model->GetMaterial()->GetPixelShader()->SetMatrix4x4("invViewProj", ((DXCamera3D*)camera)->InvViewProj());
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txDiffuse", m_DefferedBuffers->GetShaderResourceView(0));
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txNormal", m_DefferedBuffers->GetShaderResourceView(1));
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txWorld", m_DefferedBuffers->GetShaderResourceView(2));
		_model->GetMaterial()->GetPixelShader()->VSetSamplerState("samLinear", m_FinalPassSS);
		_model->GetMaterial()->GetPixelShader()->VSetFloat("width", camera->VGetViewport().width);
		_model->GetMaterial()->GetPixelShader()->VSetFloat("height", camera->VGetViewport().height);

		_model->VRender(0.0f, 0.0f, camera);

		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txDiffuse", NULL);
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txNormal", NULL);
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txWorld", NULL);

		m_ImmediateContext->OMSetBlendState(NULL, NULL, 0xfffffffff);
		m_ImmediateContext->OMSetDepthStencilState(NULL, 0);
	}

	void DXRenderer::VLightPass(ICamera3D* camera, Model* model, std::vector<SpotLight*>& lights)
	{
		std::vector<SpotLight> data;
		std::transform(lights.begin(), lights.end(), std::back_inserter(data),
			[](SpotLight* light) { return *light; });
		
		if (data.size() <= 0) return;

		m_spotLightBuffer->VUpdateSubData(0, sizeof(SpotLight), data.size(), &data[0]);
		//this->VLightPass(camera, model);


		using namespace DirectX;

		//m_DefferedBuffers->ClearDepthStencil(m_ImmediateContext);
		//m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);
		m_DefferedBuffers->BindRenderTarget(3, m_ImmediateContext);

		float blendFactor[4];


		// Setup the blend factor.
		blendFactor[0] = 1.0f;
		blendFactor[1] = 1.0f;
		blendFactor[2] = 1.0f;
		blendFactor[3] = 1.0f;

		m_ImmediateContext->OMSetBlendState(m_lightBlendState, blendFactor, 0xffffffff);
		m_ImmediateContext->OMSetDepthStencilState(m_lightDSState, 0);
		//->OMSetBlendState(m_lightBlendState, NULL, 0xfffffffff);

		DXModel* _model = (DXModel*)model;

		_model->GetMaterial()->GetVertexShader()->VSetShaderResourceView("LightBuffer", m_spotLightBuffer->GetSRV());
		_model->GetMaterial()->GetPixelShader()->SetMatrix4x4("invViewProj", ((DXCamera3D*)camera)->InvViewProj());
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txDiffuse", m_DefferedBuffers->GetShaderResourceView(0));
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txNormal", m_DefferedBuffers->GetShaderResourceView(1));
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txWorld", m_DefferedBuffers->GetShaderResourceView(2));
		_model->GetMaterial()->GetPixelShader()->VSetSamplerState("samLinear", m_FinalPassSS);
		_model->GetMaterial()->GetPixelShader()->VSetFloat("width", camera->VGetViewport().width);
		_model->GetMaterial()->GetPixelShader()->VSetFloat("height", camera->VGetViewport().height);

		_model->VRender(0.0f, 0.0f, camera);

		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txDiffuse", NULL);
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txNormal", NULL);
		_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txWorld", NULL);

		m_ImmediateContext->OMSetBlendState(NULL, NULL, 0xfffffffff);
		m_ImmediateContext->OMSetDepthStencilState(NULL, 0);

	}

	void DXRenderer::VLightPass(ICamera3D* camera, Model* model)
	{
		//using namespace DirectX;

		////m_DefferedBuffers->ClearDepthStencil(m_ImmediateContext);
		////m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);
		//m_DefferedBuffers->BindRenderTarget(3, m_ImmediateContext);

		//float blendFactor[4];


		//// Setup the blend factor.
		//blendFactor[0] = 1.0f;
		//blendFactor[1] = 1.0f;
		//blendFactor[2] = 1.0f;
		//blendFactor[3] = 1.0f;

		//m_ImmediateContext->OMSetBlendState(m_lightBlendState, blendFactor, 0xffffffff);
		//m_ImmediateContext->OMSetDepthStencilState(m_lightDSState, 0);
		////->OMSetBlendState(m_lightBlendState, NULL, 0xfffffffff);

		//DXModel* _model = (DXModel*)model;

		//_model->GetMaterial()->GetVertexShader()->VSetShaderResourceView("LightBuffer", m_lightBuffer->GetSRV());
		//_model->GetMaterial()->GetPixelShader()->SetMatrix4x4("invViewProj", ((DXCamera3D*)camera)->InvViewProj());
		//_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txDiffuse", m_DefferedBuffers->GetShaderResourceView(0));
		//_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txNormal", m_DefferedBuffers->GetShaderResourceView(1));
		//_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txWorld", m_DefferedBuffers->GetShaderResourceView(2));
		//_model->GetMaterial()->GetPixelShader()->VSetSamplerState("samLinear", m_FinalPassSS);
		//_model->GetMaterial()->GetPixelShader()->VSetFloat("width", camera->VGetViewport().width);
		//_model->GetMaterial()->GetPixelShader()->VSetFloat("height", camera->VGetViewport().height);

		//_model->VRender(0.0f, 0.0f, camera);

		//_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txDiffuse", NULL);
		//_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txNormal", NULL);
		//_model->GetMaterial()->GetPixelShader()->VSetShaderResourceView("txWorld", NULL);

		//m_ImmediateContext->OMSetBlendState(NULL, NULL, 0xfffffffff);
		//m_ImmediateContext->OMSetDepthStencilState(NULL, 0);
	}

	void DXRenderer::ReleaseBuffers()
	{
		//need to release existing buffers
		ReleaseCOM(m_RenderTargetView);
		ReleaseCOM(m_DepthStencView);

	}

	void DXRenderer::VBeginDeferred()
	{
		m_DefferedBuffers->BindRenderTargets(m_ImmediateContext);
	}

	void DXRenderer::VRenderBackBuffer()
	{
        //m_DefferedBuffers->UnbindRenderTargets(m_ImmediateContext);
		m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencView);

		m_FinalPassPS->VSetSamplerState("samLinear", m_FinalPassSS);
        m_FinalPassPS->VSetShaderResourceView("txDiffuse", m_DefferedBuffers->GetShaderResourceView(0));
        m_FinalPassPS->VSetShaderResourceView("txNormal", m_DefferedBuffers->GetShaderResourceView(1));
		m_FinalPassPS->VSetShaderResourceView("txWorld", m_DefferedBuffers->GetShaderResourceView(2));
		m_FinalPassPS->VSetShaderResourceView("txLight", m_DefferedBuffers->GetShaderResourceView(3));

		m_FinalPassVS->Activate();
		m_FinalPassPS->Activate();

		UINT stride = sizeof(DXVertexPosTex);
		UINT offset = 0;
		ID3D11Buffer* nothing = NULL;
        m_ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_ImmediateContext->IASetVertexBuffers(0, 1, &nothing, &stride, &offset);
		m_ImmediateContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);

		m_ImmediateContext->Draw(3, 0);

        m_FinalPassPS->VSetShaderResourceView("txDiffuse", 0);
        m_FinalPassPS->VSetShaderResourceView("txNormal", 0);
		m_FinalPassPS->VSetShaderResourceView("txWorld", 0);
		m_FinalPassPS->VSetShaderResourceView("txLight", 0);

        m_FinalPassVS->Deactivate();
        m_FinalPassPS->Deactivate();
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

        RECT r = { 0 };
        GetClientRect(m_HWND, &r);
		float x = position.x;
		if (position.x == -1) {
           
			float midX = static_cast<float>(((r.right - r.left) - font->VBounds(text).w) / 2);
			x = midX;
		}
		float y = position.y;
		if (position.y == -1) {
			float midY = static_cast<float>(((r.bottom-r.top) - font->VBounds(text).h) / 2);
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
