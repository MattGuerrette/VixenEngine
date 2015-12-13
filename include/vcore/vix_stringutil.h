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

#ifndef VIX_STRINGUTIL_H
#define VIX_STRINGUTIL_H

#include <vix_platform.h>
#include <string>
#include <sstream>
#include <vector>
#ifndef VIX_SYS_LINUX
#include <codecvt>
#endif
#include <iostream>

/*Unicode MACRO definitions*/
#ifdef UNICODE
#define _VTEXT(x) L##x
#define VTEXT(x) _VTEXT(x)
#else
#define VTEXT(x) x
#endif


namespace Vixen {


		VIX_API
		void str_replaceAll(std::string& input,
			                const std::string& from,
			                const std::string& to);

		template<typename T>
		inline VIX_API std::vector<T> parse(const std::string s, const char delim)
		{
			std::stringstream ss(s);
			std::string item;
			std::vector<T> elems;
			while (std::getline(ss, item, delim)) {
				if (!item.empty()) {
					std::stringstream es(item);
					T t;
					es >> t;
					elems.push_back(t);
				}
			}

			return elems;
		}
}



#endif
