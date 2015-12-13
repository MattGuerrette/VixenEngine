/**
**    Vixen Engine
**    Copyright(c) 2015 Matt Guerrette
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
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

    static const std::string WIN_PATH_DELIM  = VTEXT("\\");
    static const std::string UNIX_PATH_DELIM = VTEXT("/");

    VIX_API void            os_mkdir(const std::string& dir);
    VIX_API bool            os_isdir(const std::string& dir);
    VIX_API std::string     os_path(const std::string& path);
    VIX_API std::string     os_dir(const std::string& path, bool wt = true);
    VIX_API std::string     os_exec_dir();
}


#endif
