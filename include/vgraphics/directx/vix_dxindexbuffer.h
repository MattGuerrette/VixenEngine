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
