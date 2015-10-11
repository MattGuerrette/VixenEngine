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
