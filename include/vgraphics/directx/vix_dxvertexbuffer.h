#ifndef VIX_DXVERTEXBUFFER_H
#define VIX_DXVERTEXBUFFER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_vertexbuffer.h>

namespace Vixen {

    class VIX_API DXVPCBuffer: public IVertexBuffer
    {
    public:
        DXVPCBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXVPCBuffer();

        void VSetData(const void* data);
        void VBind();
        void VUnbind();

   
    private:
        ID3D11Device*           m_device;
        ID3D11DeviceContext*    m_context;
        ID3D11Buffer*           m_buffer;
    };

    class VIX_API DXVPTBuffer : public IVertexBuffer
    {
    public:
        DXVPTBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXVPTBuffer();

        void VSetData(const void* data);
        void VBind();
        void VUnbind();

    private:
        ID3D11Device*          m_device;
        ID3D11DeviceContext*   m_context;
        ID3D11Buffer*          m_buffer;
    };
}

#endif
