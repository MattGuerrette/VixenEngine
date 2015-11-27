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

#include <vix_glbuffers.h>

namespace Vixen {

	GLBuffer::GLBuffer(GLenum target,
					   size_t stride,
					   size_t count,
		               const GLvoid* data)
	{
		m_target = target;
		m_stride = stride;
		m_size = stride * count;
		m_count = count;

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
		glBindBuffer(m_target, 0);
	}
}
