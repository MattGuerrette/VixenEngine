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