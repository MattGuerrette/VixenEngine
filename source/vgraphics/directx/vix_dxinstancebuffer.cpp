#include <vix_dxinstancebuffer.h>


namespace Vixen {

    DXInstanceBuffer::DXInstanceBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_count = count;
        m_device = device;
        m_context = context;
        m_buffer = nullptr;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(DXInstanceData) * m_count;
        bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bd.StructureByteStride = sizeof(DXInstanceData);
        m_device->CreateBuffer(&bd, nullptr, &m_buffer);


        D3D11_SHADER_RESOURCE_VIEW_DESC svd;
        ZeroMemory(&svd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
        svd.Format = DXGI_FORMAT_UNKNOWN;
        svd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        svd.Buffer.ElementWidth = sizeof(DXInstanceData);
        svd.Buffer.ElementOffset = 0;
        svd.Buffer.NumElements = m_count;
        svd.Buffer.FirstElement = 0;
      
        m_device->CreateShaderResourceView(m_buffer, &svd, &m_srv);
        
    }

    DXInstanceBuffer::~DXInstanceBuffer()
    {
        ReleaseCOM(m_buffer);
        ReleaseCOM(m_srv);
    }

    void DXInstanceBuffer::VSetData(const void* data)
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(DXInstanceData) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        m_device->CreateBuffer(&bd, &InitData, &m_buffer);
    }

    void DXInstanceBuffer::VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data)
    {

        HRESULT hr = S_OK;

        D3D11_MAP type = (offset <= 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
        D3D11_MAPPED_SUBRESOURCE map;
        hr = m_context->Map(m_buffer, 0, type, 0, &map);
        if (SUCCEEDED(hr))
        {
            memcpy(map.pData, data, stride * count);
        }
        m_context->Unmap(m_buffer, 0);

    }

    void DXInstanceBuffer::VBind()
    {
        unsigned stride = sizeof(DXInstanceData);
        unsigned offset = 0;
        m_context->IASetVertexBuffers(0, 1, &m_buffer, &stride, &offset);
    }

    void DXInstanceBuffer::VUnbind()
    {
        m_context->IASetVertexBuffers(0, 1, nullptr, NULL, NULL);
    }

    ID3D11ShaderResourceView* DXInstanceBuffer::GetSRV()
    {
        return m_srv;
    }

}