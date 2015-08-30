#include <vix_dxvertexbuffer.h>

namespace Vixen {

    DXVPCBuffer::DXVPCBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_device = device;
        m_context = context;
        m_buffer = nullptr;
        m_count = count;
    }

    DXVPCBuffer::~DXVPCBuffer()
    {
        ReleaseCOM(m_buffer);
    }

    void DXVPCBuffer::VSetData(const void* data)
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(DXVertexPosColor) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        m_device->CreateBuffer(&bd, &InitData, &m_buffer);
    }

    void DXVPCBuffer::VBind()
    {
        unsigned stride = sizeof(DXVertexPosColor);
        unsigned offset = 0;
        m_context->IASetVertexBuffers(0, 1, &m_buffer, &stride, &offset);
    }

    void DXVPCBuffer::VUnbind()
    {
        m_context->IASetVertexBuffers(0, 1, nullptr, NULL, NULL);
    }


    //////////////////////////////////////////////////////////////////////////////////////////////
    // DX Vertex Pos Texture Buffer
    //////////////////////////////////////////////////////////////////////////////////////////////


    DXVPTBuffer::DXVPTBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_device = device;
        m_context = context;
        m_buffer = nullptr;
    }

    DXVPTBuffer::~DXVPTBuffer()
    {
        ReleaseCOM(m_buffer);
    }

    void DXVPTBuffer::VSetData(const void* data)
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(DXVertexPosTex) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        m_device->CreateBuffer(&bd, &InitData, &m_buffer);
    }

    void DXVPTBuffer::VBind()
    {
        unsigned stride = sizeof(DXVertexPosTex);
        unsigned offset = 0;
        m_context->IASetVertexBuffers(0, 1, &m_buffer, &stride, &offset);
    }

    void DXVPTBuffer::VUnbind()
    {
        m_context->IASetVertexBuffers(0, 1, nullptr, NULL, NULL);
    }



}