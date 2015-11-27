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

#ifndef VIX_FILEMANAGER_H
#define VIX_FILEMANAGER_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_singleton.h>
#include <vix_stlutil.h>

namespace Vixen {

    class VIX_API FileManager : public Singleton<FileManager>
    {
        typedef std::map<UString, File*> FileList;
    public:
        ~FileManager();

        static void     Initialize();
        static void     DeInitialize();
        static File*    OpenFile(UString filePath, FileMode mode);
        static void     CloseFile(File* file);
        static void     CloseFile(UString filePath);
        static File*    AccessFile(UString filePath);
        static size_t   TotalFilesOpen();
        static size_t   TotalBytesOpen();
        static void     PrintOpen();
    private:
        FileList   m_files;
        size_t     m_totalOpenBytes;
        size_t     m_totalOpenFiles;
    };

}

#endif
