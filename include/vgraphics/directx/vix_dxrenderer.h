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

        void    VApplyRenderMode() override;

        void	VApplyFaceCulling() override;

        void	VApplyFaceWinding() override;

        void    VSwapBuffers() override;

        void    VAttachNativeHandle(void* handle) override;

        void    VRenderTexture2D(ITexture* texture, const Transform& transform, const Rect& source) override;

        ID3D11Device* Device();

        ID3D11DeviceContext* DeviceContext();

        DXSpriteBatcher* SpriteBatch();

    private:
        DirectX::XMVECTORF32    m_clearColor;
        ID3D11Device*           m_Device;
        ID3D11DeviceContext*    m_ImmediateContext;
        ID3D11RenderTargetView* m_RenderTargetView;
        ID3D11DepthStencilView* m_DepthStencView;
        IDXGISwapChain*         m_SwapChain;
        D3D_FEATURE_LEVEL       m_FeatureLevel;
        HWND                    m_HWND;

        DXCamera2D*             m_camera2D;
        DXSpriteBatcher*        m_spriteBatch;
    };

}

#endif