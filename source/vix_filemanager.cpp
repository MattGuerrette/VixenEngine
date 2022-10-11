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

#include <vix_filemanager.h>
#include <vix_debugutil.h>

namespace Vixen {

    FileManager::~FileManager()
    {

    }

    void FileManager::Initialize()
    {
        FileManager& manager = FileManager::instance();

        manager.m_totalOpenBytes = 0;
        manager.m_totalOpenFiles = 0;
    }

    void FileManager::DeInitialize()
    {
        STLMAP_DELETE(FileManager::instance().m_files);
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

    File* FileManager::OpenFile(UString filePath, FileMode mode)
    {

        FileManager& manager = FileManager::instance();

        File* file = new File;
        if(file->Open(filePath, mode))
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
