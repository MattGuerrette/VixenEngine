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
	}
	
	uint32_t Asset::RefCount()
	{
		return m_refCount;
	}

	UString Asset::FileName()
	{
		return m_fileName;
	}

	void Asset::SetFileName(UString fileName)
	{
		m_fileName = fileName;
	}
}