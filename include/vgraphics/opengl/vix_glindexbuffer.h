#ifndef VIX_GLINDEXBUFFER_H
#define VIX_GLINDEXBUFFER_H

#include <vix_platform.h>
#include <vix_indexbuffer.h>
#include <vix_gl.h>

namespace Vixen {

	class VIX_API GLIndexBuffer : public IIndexBuffer
	{
	public:
		GLIndexBuffer(size_t count);

		~GLIndexBuffer();

		void VSetData(const unsigned short* data);
		void VBind();
		void VUnbind();

	private:
		GLuint  m_buffer;
		GLenum m_target;
	};
}

#endif