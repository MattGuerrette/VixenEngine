#include <vix_asset.h>

namespace Vixen {

	Asset::Asset()
	{
		m_refCount = 0;
	}

	void Asset::IncrementRefCount()
	{
		m_refCount++;
	}

	void Asset::DecrementRefCount()
	{
		m_refCount--;

		if (m_refCount <= 0)
			delete this;
	}
	
	uint32_t Asset::RefCount()
	{
		return m_refCount;
	}
}