/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

        void    VSwapBuffers() override;

        void    VAttachNativeHandle(void* handle) override;

        void    VRenderTexture2D(ITexture* texture, const Vector2& position, const Rect& source) override;

        void    VRenderText2D(IFont* font, UString text, const Vector2& position) override;

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
