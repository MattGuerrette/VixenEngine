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

#ifndef VIX_PIXELSHADER_H
#define VIX_PIXELSHADER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_dxshader.h>

namespace Vixen {

    class VIX_API DXPixelShader : public DXShader
    {
    public:
        DXPixelShader(ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXPixelShader();

        ID3D11PixelShader* GetShader();


        bool VSetShaderResourceView(std::string name, ID3D11ShaderResourceView* rv);
        bool VSetSamplerState(std::string name, ID3D11SamplerState* ss);

    protected:
        bool VInitShader(File* file) override;
        void VBind() override;
        void VUnbind() override;

    private:
        ID3D11PixelShader* m_shader;

    };

}

#endif
