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

#include <vix_filemanager.h>
#include <vix_debugutil.h>

namespace Vixen {

    FileManager::~FileManager()
    {
        STLMAP_DELETE(FileManager::m_files);
    }

    void FileManager::Initialize()
    {
        FileManager& manager = FileManager::instance();

        manager.m_totalOpenBytes = 0;
        manager.m_totalOpenFiles = 0;
    }

    void FileManager::PrintOpen()
    {
        FileManager& manager = FileManager::instance();

        int i = 0;
        DebugPrintF(VTEXT("Open File List:\n"));
        for(auto it = manager.m_files.begin(); it != manager.m_files.end(); it++)
        {
            File* file = it->second;
            DebugPrintF(VTEXT("\tFile[%i]: %s\n"), i, file->FilePath().c_str());
            i++;
        }
    }

    File* FileManager::OpenFile(UString filePath)
    {

        FileManager& manager = FileManager::instance();

        File* file = new File;
        if(file->Open(filePath))
        {
            //Add file to file manager
            manager.m_files[filePath] = file;

            //Add to total open bytes
            manager.m_totalOpenBytes += file->SizeBytes();

            //Add to toal open files
            manager.m_totalOpenFiles++;

            return file;
        }
        else
            delete file;

        return NULL;
    }

    void FileManager::CloseFile(File* file)
    {
        FileManager& manager = FileManager::instance();


        if (file) {
            UString filePath = file->FilePath();

            //Close file
            file->Close();

            //Remove bytes from counter
            manager.m_totalOpenBytes -= file->SizeBytes();

            STLMAP_DELETE(manager.m_files, filePath);
        }
    }

    void FileManager::CloseFile(UString filePath)
    {
        FileManager& manager = FileManager::instance();

        File* file = NULL;

        auto search = manager.m_files.find(filePath);
        if(search != manager.m_files.end()) {
            //File found
            file = search->second;
        }
        else {
            //File not found
            DebugPrintF(VTEXT("File: %s\nNot Found.\n"), filePath.c_str());
        }

        if(file) {
            //Close file
            file->Close();

            //Remove bytes from counter
            manager.m_totalOpenBytes -= file->SizeBytes();

            STLMAP_DELETE(manager.m_files, filePath);
        }

    }

    File* FileManager::AccessFile(UString filePath)
    {
        FileManager& manager = FileManager::instance();

        File* file = NULL;

        auto search = manager.m_files.find(filePath);
        if(search != manager.m_files.end()) {
            //File found
            file = search->second;
        }
        else {
            //File not found
            DebugPrintF(VTEXT("File: %s\nNot Found."), filePath.c_str());
        }

        return file;
    }

    size_t FileManager::TotalFilesOpen()
    {
        return FileManager::instance().m_totalOpenFiles;
    }

    size_t FileManager::TotalBytesOpen()
    {
        return FileManager::instance().m_totalOpenBytes;
    }

}
