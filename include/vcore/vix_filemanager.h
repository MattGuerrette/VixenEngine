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
        static File*    OpenFile(UString filePath);
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
