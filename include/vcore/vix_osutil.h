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
