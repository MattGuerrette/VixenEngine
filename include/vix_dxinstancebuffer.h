#ifndef VIX_DXINSTANCEBUFFER_H
#define VIX_DXINSTANCEBUFFER_H

#include "vix_platform.h"
#include "vix_instancebuffer.h"
#include "vix_directx.h"

namespace Vixen {

    struct DXInstanceData
    {
        DirectX::XMFLOAT4X4 world;
    };

    class VIX_API DXInstanceBuffer : public InstanceBuffer
    {
    public:
        DXInstanceBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXInstanceBuffer();

        void VSetData(const void* data);
        void VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data);
        void VBind();
        void VUnbind();

        ID3D11ShaderResourceView* GetSRV();

    private:
        ID3D11Device*          m_device;
        ID3D11DeviceContext*   m_context;
        ID3D11Buffer*          m_buffer;

        ID3D11ShaderResourceView* m_srv;
    };

}

#endif