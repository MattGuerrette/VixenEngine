#ifndef VIX_INDEXBUFFER_H
#define VIX_INDEXBUFFER_H

#include <vix_platform.h>

namespace Vixen {

    class VIX_API IIndexBuffer
    {
    public:
        virtual ~IIndexBuffer() { }

        virtual void VSetData(const unsigned short* data) = 0;
        virtual void VBind() = 0;
        virtual void VUnbind() = 0;

    protected:
        size_t m_size;
        size_t m_count;
    };

}

#endif
