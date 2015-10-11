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


#ifndef VIX_GLBUFFERS_H
#define VIX_GLBUFFERS_H

#include <vix_platform.h>
#include <vix_gl.h>

namespace Vixen {

	class VIX_API GLBuffer
	{
	public:
		GLBuffer(GLenum target,
			     size_t stride,
				 size_t count,
				 const GLvoid* data);

		virtual ~GLBuffer();

		/*bind GLBuffer to pipeline*/
		void bind();

		/*unbind GLBuffer from pipeline*/
		void unbind();

	protected:
		/*Sets buffer data*/
		void set(size_t offset, size_t stride, size_t count, const GLvoid* data);

	protected:
		GLuint   m_buffer;   /*OpenGL buffer handle*/
		GLenum   m_target;   /*OpenGL buffer target*/
		size_t   m_size;     /*buffer size*/
		size_t   m_stride;   /*size in bytes of data type*/
		size_t   m_count;    /*num elements held in buffer*/
	};

	template <typename Vertex>
	class VIX_API GLVertexBuffer : public GLBuffer
	{
	public:
		GLVertexBuffer(size_t vertex_cnt,
			           const Vertex* data = NULL)
			: GLBuffer(GL_ARRAY_BUFFER, get_stride(), vertex_cnt, data)
		{

		}

		void set(size_t offset, size_t count, const GLvoid* data = NULL)
		{
			GLBuffer::set(offset, get_stride(), count, data);
		}

		size_t get_stride() const { return sizeof(Vertex); }
	};

	class VIX_API GLIndexBuffer : public GLBuffer
	{
	public:
		GLIndexBuffer(size_t index_cnt, const unsigned short* data = NULL)
			: GLBuffer(GL_ELEMENT_ARRAY_BUFFER, get_stride(), index_cnt, data)
		{

		}

		void set(size_t offset, size_t count, const GLvoid* data)
		{
			GLBuffer::set(offset, get_stride(), count, data);
		}

		size_t get_stride() const { return sizeof(unsigned short); }
	};
}

#endif
