#ifndef VIX_FILEMANAGER_H
#define VIX_FILEMANAGER_H

#include <vix_platform.h>
#include <vix_file.h>
#include <vix_stlutil.h>

namespace Vixen {

    class VIX_API FileManager
    {
        typedef std::vector<File*> FileList;
    public:
        FileManager();

    private:
        FileList   m_files;
    };

}

#endif
