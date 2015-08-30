#include <vix_dxindexbuffer.h>

namespace Vixen {

    DXIndexBuffer::DXIndexBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_device = device;
        m_context = context;
        m_count = count;
    }
    
    DXIndexBuffer::~DXIndexBuffer()
    {
        ReleaseCOM(m_buffer);
    }

    void DXIndexBuffer::VSetData(const unsigned short* data)
    {
        D3D11_BUFFER_DESC ibd;
        ZeroMemory(&ibd, sizeof(ibd));
        ibd.Usage = D3D11_USAGE_DEFAULT;
        ibd.ByteWidth = sizeof(unsigned short) * m_count;
        ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        ibd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA IndexInitData;
        ZeroMemory(&IndexInitData, sizeof(IndexInitData));
        IndexInitData.pSysMem = data;
        m_device->CreateBuffer(&ibd, &IndexInitData, &m_buffer);
    }

    void DXIndexBuffer::VBind()
    {
        m_context->IASetIndexBuffer(m_buffer, DXGI_FORMAT_R16_UINT, 0);
    }

    void DXIndexBuffer::VUnbind()
    {
        m_context->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
    }

}