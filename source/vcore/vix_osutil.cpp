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

#include <vix_osutil.h>

#ifdef VIX_SYS_WINDOWS
	#include <direct.h>   //iso c++
	#include <windows.h>
	#ifndef NOMINMAX
	#define NOMINMAX
	#endif
#elif defined(VIX_SYS_LINUX)
	#include <sys/stat.h> //linux
	#include <sys/types.h>
	#include <unistd.h>
	#include <linux/limits.h>
#endif

namespace Vixen {


	void os_mkdir(const std::string& dir)
	{
#ifdef VIX_SYS_WINDOWS
			_mkdir(dir.c_str());
#elif  defined(VIX_SYS_LINUX)
		mkdir(dir.c_str(), S_IRWXU);
#endif
	}

	bool os_isdir(const std::string& dir)
	{
		//convert path
		std::string path = os_path(dir);
#ifdef VIX_SYS_WINDOWS
		DWORD dwAttrib = GetFileAttributes(dir.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
				(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#elif defined(VIX_SYS_LINUX)
		//THIS CODE *SHOULD* WORK ON LINUX AND UNIX.
		//IM NOT 100% POSITIVE THOUGH, SO PLEASE CHECK
		struct stat info;
		stat(dir.c_str(), &info);
		return S_ISDIR(info.st_mode);
#endif
	}

	std::string os_path(const std::string& path)
	{
		std::string temp = path;
#ifdef VIX_SYS_WINDOWS
		str_replaceAll(temp, UNIX_PATH_DELIM, WIN_PATH_DELIM);
#else
		str_replaceAll(temp, "\\", "/");
#endif
		return temp;
	}

	std::string os_dir(const std::string& path, bool wt)
	{
		std::string dir = "";
		if (path.empty())
			return dir;

		//remove trailing slash for now
		dir = path.substr(0, path.size() - 1);

		size_t back_slash = 0;
		char   c_slash;
#ifdef VIX_SYS_WINDOWS
		c_slash = WIN_PATH_DELIM[0];
		back_slash = dir.find_last_of(c_slash);
#else
		c_slash = UNIX_PATH_DELIM[0];
		back_slash = dir.find_last_of(c_slash);
#endif
		if (back_slash != std::string::npos)
			dir = dir.substr(0, back_slash);
		if (wt)
			dir += c_slash;

		return dir;

	}

	std::string os_exec_dir()
	{
#ifdef VIX_SYS_WINDOWS
		char path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);
		return os_dir(path);
#else
        char arg1[20];
        char exepath[PATH_MAX + 1] = {0};
        sprintf( arg1, "/proc/%d/exe", getpid() );
        readlink( arg1, exepath, 1024 );
        return os_dir(exepath);
#endif
	}

}
