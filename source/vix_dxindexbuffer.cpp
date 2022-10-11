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

#include <vix_dxindexbuffer.h>

namespace Vixen {

    DXIndexBuffer::DXIndexBuffer(size_t count, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        m_device = device;
        m_context = context;
        m_count = count;
        m_buffer = nullptr;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = sizeof(unsigned short) * m_count;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        m_device->CreateBuffer(&bd, nullptr, &m_buffer);
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

    void DXIndexBuffer::VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data)
    {
        HRESULT hr = S_OK;

        D3D11_MAP type = D3D11_MAP_WRITE_NO_OVERWRITE;
        D3D11_MAPPED_SUBRESOURCE map;
        hr = m_context->Map(m_buffer, 0, type, 0, &map);
        if (SUCCEEDED(hr))
        {
            unsigned short* _dest = ((unsigned short*)map.pData) + offset;
            memcpy((void*)_dest, data, stride * count);
        }
        m_context->Unmap(m_buffer, 0);
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
