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
