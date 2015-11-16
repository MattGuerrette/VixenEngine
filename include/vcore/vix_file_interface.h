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

    //File mode
    enum class FileMode
    {
        ReadText,
        ReadBinary,
        WriteText,
        WriteBinary,
        AppendText,
        AppendBinary
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
        virtual bool      Open(UString path, FileMode mode) = 0;
        virtual bool      Flush() = 0;
        virtual bool      Seek(size_t offset, FileSeek mode) = 0;
        virtual bool      Close() = 0;
        virtual size_t    Read(BYTE* out, size_t len) = 0;
        virtual size_t    Write(BYTE* in, size_t len) = 0;
        virtual size_t    Tell() = 0;
        virtual size_t    SizeBytes() = 0;
        virtual size_t    SizeKBytes() = 0;
        virtual size_t    Position() = 0;
        virtual FILE*     Handle() = 0;
        virtual bool      PError(int err = 0) =  0;
    };

}

#endif
