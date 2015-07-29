#ifndef VIX_DXRENDERER_H
#define VIX_DXRENDERER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_renderer.h>
#include <vix_dxprimitivecube.h>

namespace Vixen {




    class VIX_API DXRenderer : public IRenderer
    {
    public:
        DXRenderer(HWND hd);

        ~DXRenderer();

        bool VInitialize() override;

        void VDeInitialize() override;

        void VRender();


    private:
        ID3D11Device*           m_Device;
        ID3D11DeviceContext*    m_ImmediateContext;
        ID3D11RenderTargetView* m_RenderTargetView;
        ID3D11DepthStencilView* m_DepthStencView;
        ID3D11VertexShader*     m_VShader;
        ID3D11PixelShader*      m_PShader;
        ID3D11InputLayout*      m_InputLayout;
        ID3D11Buffer*           m_VBuffer;
        ID3DBlob*               m_VSBlob;
        ID3DBlob*               m_PSBlob;
        IDXGISwapChain*         m_SwapChain;
        ID3D11Buffer*           m_ConstantBuffer;
        DirectX::XMMATRIX       m_World;
        DirectX::XMMATRIX       m_View;
        DirectX::XMMATRIX       m_Projection;
        D3D_FEATURE_LEVEL       m_FeatureLevel;
        HWND                    m_HWND;

        Vixen::DXPrimitiveCube* m_cube;
    };

}

#endif