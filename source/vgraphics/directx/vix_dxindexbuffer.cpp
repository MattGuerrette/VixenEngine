/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
