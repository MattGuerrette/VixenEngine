#include <vix_glvertexbuffer.h>


namespace Vixen {

	GLVPCBuffer::GLVPCBuffer(size_t count)
	{
		m_count = count;

		glGenBuffers(1, &m_buffer);
	}

	GLVPCBuffer::~GLVPCBuffer()
	{
		glDeleteBuffers(1, &m_buffer);
	}

	void GLVPCBuffer::VSetData(const void* data)
	{
		
	}

}