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

#include <vix_fileutil.h>

namespace Vixen {

    std::string getFileExtension(const std::string& filePath, bool wd /* = true */)
    {
        std::string ext = "";
        size_t pos = filePath.rfind(".");
        if (pos != std::string::npos) {
            if (wd)
                ext = filePath.substr(pos);
            else
                ext = filePath.substr(pos + 1);
        }

        return ext;
    }

    std::string getFileName(const std::string& filePath, bool we /* = true */)
    {
        std::string name = "";
        std::string path = os_path(filePath);
        size_t pos = 0;
#ifdef VIX_SYS_WINDOWS
        pos = path.find_last_of(WIN_PATH_DELIM);
        if(pos != std::string::npos) {
            path.erase(0, pos + 1);
        }

#elif defined (VIX_SYS_LINUX) || defined (VIX_SYS_MACOS)
        pos = path.find_last_of(UNIX_PATH_DELIM);
        if (pos != std::string::npos) {
            path.erase(0, pos + 1);
        }
#endif

        //now remove extension if desired
        if (!we) {
            size_t extPos = path.find_last_of(".");
            path = path.substr(0, extPos);
        }

        return path;
    }

}
