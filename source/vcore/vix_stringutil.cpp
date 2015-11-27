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
