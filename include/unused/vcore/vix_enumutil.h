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

#ifndef VIX_ENUM_UTIL_H
#define VIX_ENUM_UTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>


template <typename T>
class VIX_API EnumStrings
{
public:
	static char const* m_array[];
};

template <typename T>
const std::string EnumString(T _enum)
{
	int index = static_cast<int>(_enum);

	const char* str = EnumStrings<T>::m_array[index];
	if (str)
		return std::string(str);
	else
		return "Invalid Enum";
}

#endif
