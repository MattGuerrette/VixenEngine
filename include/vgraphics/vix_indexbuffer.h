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

#ifndef VIX_INDEXBUFFER_H
#define VIX_INDEXBUFFER_H

#include <vix_platform.h>

namespace Vixen {

    class VIX_API IIndexBuffer
    {
    public:
        virtual ~IIndexBuffer() { }

        virtual void VSetData(const unsigned short* data) = 0;
        virtual void VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data) = 0;
        virtual void VBind() = 0;
        virtual void VUnbind() = 0;

    protected:
        size_t m_size;
        size_t m_count;
    };

}

#endif
