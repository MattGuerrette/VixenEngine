#ifndef VIX_GLVERTEXBUFFER_H
#define VIX_GLVERTEXBUFFER_H

#include <vix_platform.h>
#include <vix_vertexbuffer.h>

namespace Vixen {

	class VIX_API GLVPCBuffer : public IVertexBuffer
	{
	public:
		GLVPCBuffer(size_t count);

		~GLVPCBuffer();

		void VSetData(const void* data);
		void VBind();
		void VUnbind();

	private:
		GLuint m_buffer;

	};

}

#endif