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
#include <vix_dxspritebatcher.h>

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

        void    VSwapBuffers() override;

        void    VInitializeSpriteBatch() override;

        void    VAttachNativeHandle(void* handle) override;

        void    VRenderTexture2D(Texture* texture, const Vector2& position, const Rect& source) override;

        void    VRenderText2D(Font* font, UString text, const Vector2& position) override;

        void    VResizeBuffers(uint32_t width, uint32_t height) override;

		ICamera2D* VCamera2D();

        ID3D11Device* Device();

        ID3D11DeviceContext* DeviceContext();

        DXSpriteBatcher* SpriteBatch();

    private:
        bool CreateBuffers(uint32_t width, uint32_t height);
        void ReleaseBuffers();


    private:
        DirectX::XMVECTORF32    m_clearColor;
        ID3D11Device*           m_Device;
        ID3D11DeviceContext*    m_ImmediateContext;
        ID3D11RenderTargetView* m_RenderTargetView;
        ID3D11DepthStencilView* m_DepthStencView;
        IDXGISwapChain*         m_SwapChain;
        DXGI_SWAP_CHAIN_DESC    m_SwapChainDesc;
        D3D_FEATURE_LEVEL       m_FeatureLevel;
        HWND                    m_HWND;

        DXCamera2D*             m_camera2D;
        DXSpriteBatcher*        m_spriteBatch;
    };

}

#endif
