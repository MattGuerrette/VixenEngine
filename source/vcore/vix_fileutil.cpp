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

#include <vix_fileutil.h>

namespace Vixen {

    UString getFileExtension(const UString& filePath, bool wd /* = true */)
	{
		UString ext = VTEXT("");
		size_t pos = filePath.find_first_of(VTEXT("."));
		if (pos != UString::npos) {
			if (wd)
				ext = filePath.substr(pos);
			else
				ext = filePath.substr(pos + 1);
		}

		return ext;
	}

	UString getFileName(const UString& filePath, bool we /* = true */)
	{
		UString name = VTEXT("");
		UString path = os_path(filePath);
		size_t pos = 0;
#ifdef VIX_SYS_WINDOWS
		pos = path.find_last_of(WIN_PATH_DELIM);
		if(pos != UString::npos) {
			path.erase(0, pos + 1);
		}
		
#elif defined (VIX_SYS_LINUX) || defined (VIX_SYS_MACOS)
		pos = path.find_last_of(UNIX_PATH_DELIM);
		if (pos != UString::npos) {
			path.erase(0, pos + 1);
		}
#endif

		//now remove extension if desired
		if (!we) {
			size_t extPos = path.find_last_of(VTEXT("."));
			path = path.substr(0, extPos);
		}

		return path;
	}

}
