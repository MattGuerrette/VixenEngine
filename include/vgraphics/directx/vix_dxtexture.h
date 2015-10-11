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

#ifndef VIX_DXTEXTURE_H
#define VIX_DXTEXTURE_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_freeimage.h>
#include <vix_texture.h>

namespace Vixen {

    class VIX_API DXTexture : public ITexture
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
