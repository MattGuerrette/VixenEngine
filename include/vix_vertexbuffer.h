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

#ifndef VIX_VERTEXBUFFER_H
#define VIX_VERTEXBUFFER_H

#include "vix_platform.h"

namespace Vixen {

    class VIX_API IVertexBuffer
    {
    public:
        virtual ~IVertexBuffer() { }

        virtual void VSetData(const void* data) = 0;
        virtual void VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data) = 0;
        virtual void VBind() = 0;
        virtual void VUnbind() = 0;

    protected:
        size_t   m_size;     /*buffer size*/
        size_t   m_stride;   /*size in bytes of data type*/
        size_t   m_count;    /*num elements held in buffer*/
    };

}

#endif
