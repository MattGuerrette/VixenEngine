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
