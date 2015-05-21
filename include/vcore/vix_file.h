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
#include <vix_noncopy.h>
#include <vix_stringutil.h>
#include <vix_osutil.h>

namespace Vixen {

	//Seek mode
	enum FSOrigin
	{
		FS_SEEK_CUR,
		FS_SEEK_END,
		FS_SEET_SET
	};

	class VIX_API File : public INonCopy
	{
	public:
		virtual ~File(void) { };

		virtual UString		GetName(void) = 0;
		virtual UString		GetPath(void) = 0;
		virtual int			Read(void* buffer, int len) = 0;
		virtual int			Write(const void* buffer, int len) = 0;
		virtual int			Length(void) = 0;
		virtual int			Tell(void) = 0;
		virtual int			Seek(long offset, FSOrigin origin) = 0;
	};


	/**
	*	ZipFile class
	*
	*	Describes a file contained in ZIP pak
	*/
	class VIX_API ZipFile : public File
	{
	public:
		ZipFile(void);

		~ZipFile(void);

		UString		GetName(void);
		UString		GetPath(void);
		int			Read(void* buffer, int len);
		int			Write(const void* buffer, int len);
		int			Length(void);
		int			Tell(void);
		int			Seek(long offset, FSOrigin origin);

	private:
		UString		m_name;  /*zip name*/
		UString     m_path;  /*full path with name*/
		size_t		m_size;  /*filesize*/
		BYTE*		m_data;  /*zip data*/
	};

	/*
	* Retrieves extension for file.
	* @param filePath
	* Path or Name of file
	* @param wd
	* Flag determines if user wants (.) included in extension
	*/
	VIX_API UString getFileExtension(const UString& filePath, bool wd = true);

	/*
	* Retrieves filename with extension.
	* @param filePath
	* Path of file
	*/
	VIX_API UString getFileName(const UString& filePath);

}


#endif
