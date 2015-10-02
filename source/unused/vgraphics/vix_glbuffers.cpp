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

#include <vix_glbuffers.h>

namespace Vixen {

	GLBuffer::GLBuffer(GLenum target,
					   size_t stride,
					   size_t count,
		               const GLvoid* data)
					   : m_target(target),
					     m_size(stride * count),
						 m_count(count),
						 m_stride(stride)
	{
		glGenBuffers(1, &m_buffer);
		bind();
		glBufferData(m_target, m_size, data, GL_STATIC_DRAW);
		unbind();
	}

	void GLBuffer::set(size_t offset, size_t stride, size_t count, const GLvoid* data)
	{
		bind();
		glBufferSubData(m_target, offset, stride * count, data);
		unbind();
	}

	GLBuffer::~GLBuffer()
	{
		/*delete buffer*/
		glDeleteBuffers(1, &m_buffer);
	}

	void GLBuffer::bind()
	{
		/*bind buffer to opengl*/
		glBindBuffer(m_target, m_buffer);
	}

	void GLBuffer::unbind()
	{
		/*unbind buffer from opengl*/
		glBindBuffer(m_target, NULL);
	}
}
