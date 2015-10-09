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
