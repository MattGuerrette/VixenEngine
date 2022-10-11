#ifndef VIX_DXDEFFEREDBUFFERS_H
#define VIX_DXDEFFEREDBUFFERS_H

#include "vix_platform.h"
#include "vix_directx.h"
#include "vix_color.h"

namespace Vixen {

    class VIX_API DXDefferedBuffers
    {
        static const int BUFFER_COUNT = 4;
    public:
        DXDefferedBuffers();

        ~DXDefferedBuffers();

        bool Initialize(ID3D11Device* device, uint32_t width, uint32_t height);

        void ReleaseBuffers();

        void BindRenderTargets(ID3D11DeviceContext* context);
		void BindRenderTarget(uint32_t index, ID3D11DeviceContext* context);
		void UnbindRenderTargets(ID3D11DeviceContext* context);
        void ClearRenderTargets(ID3D11DeviceContext* context, DirectX::XMVECTORF32 clearColor);
		void ClearDepthStencil(ID3D11DeviceContext* context);
            
        ID3D11ShaderResourceView* GetShaderResourceView(int index);

    private:
        ID3D11Texture2D*            m_RenderTargetTextures[BUFFER_COUNT];
        ID3D11RenderTargetView*     m_RenderTargetViews[BUFFER_COUNT];
        ID3D11ShaderResourceView*   m_ShaderResourceViews[BUFFER_COUNT];
        ID3D11Texture2D*            m_DepthStencilBuffer;
        ID3D11DepthStencilView*     m_DepthStencilView;
    };

}

#endif