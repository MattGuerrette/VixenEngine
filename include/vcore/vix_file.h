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
		virtual bool	  Open(UString path, FileMode mode);
		virtual bool      Seek(size_t offset, FileSeek mode);
		virtual size_t    Read(BYTE* out, size_t len);
        virtual size_t    Write(BYTE* in, size_t len);
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
