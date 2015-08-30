#ifndef VIX_DXINDEXBUFFER_H
#define VIX_DXINDEXBUFFER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_indexbuffer.h>

namespace Vixen {

    class VIX_API DXIndexBuffer : public IIndexBuffer
    {
    public:
        DXIndexBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context);

        ~DXIndexBuffer();

        void VSetData(const unsigned short* data);
        void VBind();
        void VUnbind();

    private:
        ID3D11Device*           m_device;
        ID3D11DeviceContext*    m_context;
        ID3D11Buffer*           m_buffer;
    };

}

#endif
