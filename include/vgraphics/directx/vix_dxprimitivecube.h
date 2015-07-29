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