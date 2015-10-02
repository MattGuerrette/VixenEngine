/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
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
