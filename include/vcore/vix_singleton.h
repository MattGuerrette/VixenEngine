/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIX_SINGLETON_H
#define VIX_SINGLETON_H

#include <vix_platform.h>
#include <vix_noncopy.h>
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
