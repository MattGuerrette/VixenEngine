#ifndef VIX_DXRENDERER_H
#define VIX_DXRENDERER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_renderer.h>
#include <vix_dxprimitivecube.h>
#include <vix_dxquad.h>
#include <vix_dxcamera2d.h>
#include <vix_dxcamera3d.h>
#include <vix_dxtexture.h>

namespace Vixen {

    class VIX_API DXRenderer : public IRenderer
    {
    public:
        DXRenderer();

        ~DXRenderer();

        bool    VInitialize()   override;

        void    VDeInitialize() override;

        void    VSetClearColor(const Color& c) override;

        void    VClearBuffer(ClearArgs args) override;

        void    VApplyRenderMode() override;

        void	VApplyFaceCulling() override;

        void	VApplyFaceWinding() override;

        void    VSwapBuffers() override;

        void    VAttachNativeHandle(void* handle) override;

    private:
        DirectX::XMVECTORF32    m_clearColor;
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

        ID3D11SamplerState*         m_SamplerState;
        ID3D11ShaderResourceView*   m_TextureRV;

        Vixen::DXPrimitiveCube* m_cube;
        Vixen::DXQuad* m_quad;
        Vixen::DXTexture* m_texture;
        Vixen::DXCamera2D* m_camera;
    };

}

#endif