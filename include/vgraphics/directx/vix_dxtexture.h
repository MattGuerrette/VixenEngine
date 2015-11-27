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

#ifndef VIX_DXTEXTURE_H
#define VIX_DXTEXTURE_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_freeimage.h>
#include <vix_texture.h>
#include <vix_asset.h>

namespace Vixen {

    class VIX_API DXTexture : public Texture
    {
    public:
        DXTexture(ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXTexture();

        bool VInitFromFile(File* file);
        bool VInitFromBMP(FREEIMAGE_BMP* bmp);

        ID3D11ShaderResourceView*  ResourceView();
        ID3D11SamplerState*        SampleState();
        size_t                     VGetWidth() const;
        size_t                     VGetHeight() const;

    private:
        ID3D11Device*              m_device;
        ID3D11DeviceContext*       m_context;
        ID3D11ShaderResourceView*  m_resourceView;
        ID3D11SamplerState*        m_sampleState;
        float                      m_width;
        float                      m_height;

    private:
        static DXGI_FORMAT FromBPP(size_t bpp);
    };

}

#endif
