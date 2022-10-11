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

#ifndef VIX_DXPRIMITIVECUBE_H
#define VIX_DXPRIMITIVECUBE_H

#include "vix_platform.h"
#include "vix_directx.h"

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
