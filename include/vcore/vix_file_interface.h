#ifndef VIX_FILE_INTERFACE_H
#define VIX_FILE_INTERFACE_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_osutil.h>

namespace Vixen {

    enum class FileError
    {
        None,           //No Error Occured
        Read,           //Error occured when reading
        Write,          //Error occured when writing
        Fatal,          //Fatal error occured
        Resource,       //Out of resources
        Open,           //File could not be opened
        Abort,          //Operation was aborted
        Timeout,        //Timeout occured
        Unspecified,    //Unspecified error occured
        Remove,         //File could not be removed
        Rename,         //File could not be renamed
        Position,       //Position in file could not be changed
        Copy            //File coult not be copied
    };

    //Seek mode
    enum class FileSeek
    {
        Current,
        End,
        Set
    };

    /**
    *
    *   IFIle interface
    *
    *   Describes base class of all File I/O classes
    */
    class VIX_API IFile : public INonCopy
    {
    public:
        virtual ~IFile() { };

        virtual FileError Error() = 0;
        virtual UString   FileName() = 0;
        virtual UString   FilePath() = 0;
        virtual UString   BaseName() = 0;
        virtual bool      Open(UString path) = 0;
        virtual bool      Flush() = 0;
        virtual bool      Seek(size_t offset, FileSeek mode) = 0;
        virtual bool      Close() = 0;
        virtual int       Read(BYTE* out, size_t len) = 0;
        virtual size_t    Tell() = 0;
        virtual size_t    SizeBytes() = 0;
        virtual size_t    SizeKBytes() = 0;
        virtual size_t    Position() = 0;
        virtual FILE*     Handle() = 0;
        virtual bool      PError(int err = 0) =  0;
    };

}

#endif
