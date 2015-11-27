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
