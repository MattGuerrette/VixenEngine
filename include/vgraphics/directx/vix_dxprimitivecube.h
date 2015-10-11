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

#ifndef VIX_DXPRIMITIVECUBE_H
#define VIX_DXPRIMITIVECUBE_H

#include <vix_platform.h>
#include <vix_directx.h>

namespace Vixen
{
    class VIX_API DXPrimitiveCube
    {
    public:
        DXPrimitiveCube();

        ~DXPrimitiveCube();

        void Initialize(ID3D11Device* device);
        void Render(ID3D11DeviceContext* context);
        void SetVertexShader(ID3D11VertexShader* vs);
        void SetPixelShader(ID3D11PixelShader* ps);
        void SetConstantBuffer(ID3D11Buffer* cb);

    private:
        ID3D11Buffer*       m_vertexBuffer;
        ID3D11Buffer*       m_indexBuffer;
        ID3D11VertexShader* m_vShader;
        ID3D11PixelShader*  m_pShader;
        ID3D11Buffer*       m_constantBuffer;
    };
}

#endif
