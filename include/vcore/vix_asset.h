#ifndef VIX_ASSET_H
#define VIX_ASSET_H

#include <vix_platform.h>
#include <cstdint>

#include <vix_file.h>

namespace Vixen {

	class VIX_API Asset
	{
	public:
		Asset();

		virtual ~Asset() { };
		
		virtual bool VInitFromFile(File* file) = 0;

		void IncrementRefCount();
		
		void DecrementRefCount();

		uint32_t RefCount();

	private:
		uint32_t m_refCount;
	};

}

#endif