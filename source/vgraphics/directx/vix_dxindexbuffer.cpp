/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

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