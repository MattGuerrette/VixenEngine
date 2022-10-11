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

    }

    void DXVPCBuffer::VSetData(const void* data)
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(DXVertexPosColor) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        m_device->CreateBuffer(&bd, &InitData, &m_buffer);
    }

    void DXVPCBuffer::VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data)
    {
        HRESULT hr = S_OK;

        D3D11_MAPPED_SUBRESOURCE map;
        hr = m_context->Map(m_buffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &map);
        if (SUCCEEDED(hr))
        {
            memcpy(map.pData, data, stride * count);
        }
        m_context->Unmap(m_buffer, 0);
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
        m_count = count;
        m_device = device;
        m_context = context;
        m_buffer = nullptr;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(DXVertexPosTex) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        m_device->CreateBuffer(&bd, nullptr, &m_buffer);

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
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        m_device->CreateBuffer(&bd, &InitData, &m_buffer);
    }

    void DXVPTBuffer::VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data)
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

    //////////////////////////////////////////////////////////////////////////////////////////////
    // DX Vertex Pos Texture Normal Buffer
    //////////////////////////////////////////////////////////////////////////////////////////////

    DXVPTNBuffer::DXVPTNBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_count = count;
        m_device = device;
        m_context = context;
        m_buffer = nullptr;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(DXVertexPosTexNormal) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        m_device->CreateBuffer(&bd, nullptr, &m_buffer);

    }

    DXVPTNBuffer::~DXVPTNBuffer()
    {
        ReleaseCOM(m_buffer);
    }

    void DXVPTNBuffer::VSetData(const void* data)
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(DXVertexPosTexNormal) * m_count;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        m_device->CreateBuffer(&bd, &InitData, &m_buffer);
    }

    void DXVPTNBuffer::VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data)
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

    void DXVPTNBuffer::VBind()
    {
        unsigned stride = sizeof(DXVertexPosTexNormal);
        unsigned offset = 0;
        m_context->IASetVertexBuffers(0, 1, &m_buffer, &stride, &offset);
    }

    void DXVPTNBuffer::VUnbind()
    {
        m_context->IASetVertexBuffers(0, 1, nullptr, NULL, NULL);
    }
}
