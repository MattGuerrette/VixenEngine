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
