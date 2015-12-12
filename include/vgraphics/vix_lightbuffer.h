#ifndef VIX_LIGHTBUFFER_H
#define VIX_LIGHTBUFFER_H

#include <vix_platform.h>

namespace Vixen {

	class VIX_API LightBuffer
	{
	public:
		virtual ~LightBuffer() { }

		virtual void VSetData(const void* data) = 0;
		virtual void VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data) = 0;
		virtual void VBind() = 0;
		virtual void VUnbind() = 0;

	protected:
		size_t   m_size;     /*buffer size*/
		size_t   m_stride;   /*size in bytes of data type*/
		size_t   m_count;    /*num elements held in buffer*/
	};

}

#endif