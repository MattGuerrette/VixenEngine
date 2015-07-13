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

    void FileManager::OpenFile(UString filePath)
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
        }
        else
            delete file;
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
            DebugPrintF(VTEXT("File: %s\nNot Found."), filePath.c_str());
        }

        if(file) {
            //Close file
            file->Close();

            //Remove bytes from counter
            manager.m_totalOpenBytes -= file->SizeBytes();
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
