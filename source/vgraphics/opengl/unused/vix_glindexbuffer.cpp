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

#include <vix_glindexbuffer.h>

namespace Vixen {

	GLIndexBuffer::GLIndexBuffer(size_t count)
	{
		m_count = count;
		m_stride = sizeof(unsigned short);
		m_target = GL_ELEMENT_ARRAY_BUFFER;

		glGenBuffers(1, &m_buffer);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_buffer);
	}

	void GLIndexBuffer::VSetData(const unsigned short* data)
	{
		VBind();
		glBufferData(m_target, m_stride * m_count, data, GL_STATIC_DRAW);
		VUnbind();
	}

	void GLIndexBuffer::VBind()
	{
		glBindBuffer(m_target, m_buffer);
	}

	void GLIndexBuffer::VUnbind()
	{
		glBindBuffer(m_target, NULL);
	}

}
