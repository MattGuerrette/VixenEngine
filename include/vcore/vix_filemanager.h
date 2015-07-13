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
        static void     OpenFile(UString filePath);
        static void     CloseFile(UString filePath);
        static File*    AccessFile(UString filePath);
        static size_t   TotalFilesOpen();
        static size_t   TotalBytesOpen();
    private:
        FileList   m_files;
        size_t     m_totalOpenBytes;
        size_t     m_totalOpenFiles;
    };

}

#endif
