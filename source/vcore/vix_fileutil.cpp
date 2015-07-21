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
