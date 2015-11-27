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
        void VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data);
        void VBind();
        void VUnbind();

    private:
        ID3D11Device*           m_device;
        ID3D11DeviceContext*    m_context;
        ID3D11Buffer*           m_buffer;
    };

}

#endif
