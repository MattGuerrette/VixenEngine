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

#include <vix_fileutil.h>

namespace Vixen {

    UString getFileExtension(const UString& filePath, bool wd /* = true */)
	{
		UString ext = VTEXT("");
		size_t pos = filePath.rfind(VTEXT("."));
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
