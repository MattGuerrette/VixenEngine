/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

#ifndef VIX_FILE_H
#define VIX_FILE_H

#include <vix_platform.h>
#include <vix_file_interface.h>
#include <cstdio>



namespace Vixen {



	class VIX_API File : public IFile
	{
	public:
		File();

		~File(void);

		virtual FileError Error();
		virtual UString   FileName();
		virtual UString   FilePath();
		virtual UString   BaseName();
		virtual bool      Flush();
		virtual bool	  Open(UString path);
		virtual bool      Seek(size_t offset, FileSeek mode);
		virtual int       Read(BYTE* out, size_t len);
		virtual bool	  Close();
		virtual size_t    Tell();
		virtual size_t    SizeBytes();
        virtual size_t    SizeKBytes();
		virtual size_t    Position();
		virtual FILE*	  Handle();
		virtual bool      PError(int err = 0);


	protected:
		FileError 	m_error;
		UString 	m_filePath;
		UString 	m_fileName;
		UString     m_baseName;
		size_t  	m_position;
		size_t  	m_size;
		FILE*       m_handle;
	};



}


#endif
