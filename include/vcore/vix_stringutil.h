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



/*Unicode system type defines*/
#if defined(VIX_SYS_WINDOWS) && defined(UNICODE)
typedef std::wstring          UString;
typedef wchar_t               UChar;
typedef std::wstringstream    USStream;
typedef std::wostream         UOStream;
typedef std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> UConverter;  //not implemented in libstd++ yet...
#else /*UNIX or not Unicode defined*/
typedef std::string           UString;
typedef char                  UChar;
typedef std::stringstream     USStream;
typedef std::ostream          UOStream;
#endif

/*Unicode MACRO definitions*/
#ifdef UNICODE
#define _VTEXT(x) L##x
#define VTEXT(x) _VTEXT(x)
#else
#define VTEXT(x) x
#endif


namespace Vixen {


		VIX_API
		void str_replaceAll(UString& input,
			                const UString& from,
			                const UString& to);

        VIX_API
        std::string UStringToStd(const UString& str);

        VIX_API
        UString UStringFromCharArray(const char* str);

		template<typename T>
		inline VIX_API std::vector<T> parse(const UString s, const UChar delim)
		{
			USStream ss(s);
			UString item;
			std::vector<T> elems;
			while (std::getline(ss, item, delim)) {
				if (!item.empty()) {
					USStream es(item);
					T t;
					es >> t;
					elems.push_back(t);
				}
			}

			return elems;
		}
}



#endif
