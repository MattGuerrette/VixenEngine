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
        DXTexture(ID3D11Device* device);

        ~DXTexture();

        bool InitFromFile(File* file);
        bool InitFromBMP(FREEIMAGE_BMP* bmp);

        ID3D11ShaderResourceView*  ResourceView();
        ID3D11SamplerState*        SampleState();
        float                      Width();
        float                      Height();

    private:
        ID3D11Device*              m_device;
        ID3D11ShaderResourceView*  m_resourceView;
        ID3D11SamplerState*        m_sampleState;

    private:
        static DXGI_FORMAT FromBPP(size_t bpp);
    };

}

#endif
