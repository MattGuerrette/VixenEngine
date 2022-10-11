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

#ifndef VIX_SINGLETON_H
#define VIX_SINGLETON_H

#include <vix_platform.h>
#include "vix_noncopy.h"
#include <cassert>
#include <memory>
#include <atomic>

namespace Vixen {

	template <typename T>
	class VIX_API Singleton : private INonCopy
	{
	public:
		static T& instance()
		{
			static T _instance;

			return _instance;
		}

	protected:
		explicit Singleton<T>() { }

	};
}

#endif