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

#ifndef VIX_GLVERTEXBUFFER_H
#define VIX_GLVERTEXBUFFER_H

#include <vix_platform.h>
#include <vix_vertexbuffer.h>

namespace Vixen {

	class VIX_API GLVPCBuffer : public IVertexBuffer
	{
	public:
		GLVPCBuffer(size_t count);

		~GLVPCBuffer();

		void VSetData(const void* data);
		void VBind();
		void VUnbind();

	private:
		GLuint m_buffer;

	};

}

#endif
