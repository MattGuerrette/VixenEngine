
/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

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

