
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

#ifndef VIX_ASSET_H
#define VIX_ASSET_H

#include <vix_platform.h>
#include <cstdint>

#include "vix_file.h"

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

		UString FileName();

		void SetFileName(UString fileName);

	private:
		UString  m_fileName;
		uint32_t m_refCount;
	};

}

#endif

