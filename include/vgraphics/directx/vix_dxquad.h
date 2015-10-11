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

#ifndef VIX_DXQUAD_H
#define VIX_DXQUAD_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_dxtexture.h>

namespace Vixen {

    class VIX_API DXQuad
    {
    public:
        DXQuad();

        ~DXQuad();

        void Initialize(ID3D11Device* device);

        void Render(ID3D11DeviceContext* context);

        void SetVertexShader(ID3D11VertexShader* vs);
        void SetPixelShader(ID3D11PixelShader* ps);
        void SetConstantBuffer(ID3D11Buffer* cb);
        void SetTexture(DXTexture* texture);
        void SetSampleState(ID3D11SamplerState* ss);
        void SetShaderResourceView(ID3D11ShaderResourceView* rv);

    private:
        ID3D11Buffer* m_vertexBuffer;
        ID3D11Buffer* m_indexBuffer;
        ID3D11VertexShader* m_vShader;
        ID3D11PixelShader*  m_pShader;
        ID3D11Buffer*       m_constantBuffer;
        DXTexture*          m_texture;
        ID3D11ShaderResourceView* m_RV;
        ID3D11SamplerState* m_SS;
        float x;
        float y;
    };

}

#endif
