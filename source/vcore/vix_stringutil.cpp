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

#include <vix_stringutil.h>

namespace Vixen {

    UString UStringFromCharArray(const char* data)
    {
        #ifdef VIX_SYS_WINDOWS
        UConverter cv;
        return cv.from_bytes(data);
        #else
        return UString(data);
        #endif
    }

    std::string UStringToStd(const UString& str)
    {
        #ifdef VIX_SYS_WINDOWS
        UConverter cv;
        return cv.to_bytes(str);
        #else
        return UString(str);
        #endif
    }

	void str_replaceAll(UString& input, const UString& from, const UString& to)
	{
		size_t pos = 0;
		while ((pos = input.find(from, pos)) != UString::npos) {
			input.replace(pos, from.length(), to);
			pos += to.length();
		}
	}
}
