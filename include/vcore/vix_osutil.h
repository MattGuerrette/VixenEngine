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

#ifndef VIX_OSUTIL_H
#define VIX_OSUTIL_H

#include <vix_platform.h>
#include <vix_stringutil.h>



namespace Vixen {

	static const UString WIN_PATH_DELIM  = VTEXT("\\");
	static const UString UNIX_PATH_DELIM = VTEXT("/");

	VIX_API void        os_mkdir(const UString& dir);
	VIX_API bool        os_isdir(const UString& dir);
	VIX_API	UString     os_path(const UString& path);
	VIX_API UString     os_dir(const UString& path, bool wt = true);
	VIX_API UString     os_exec_dir();
}


#endif
