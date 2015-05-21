/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
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

#ifndef VIX_BUFSIZE
#define VIX_BUFSIZE 1024
#endif

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
