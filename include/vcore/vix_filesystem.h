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

#ifndef VIX_FILESYSTEM_H
#define VIX_FILESYSTEM_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_stringutil.h>

namespace Vixen {

	enum FSMode
	{
		FS_READ,
		FS_WRITE,
		FS_APPEND
	};

	class VIX_API FileList
	{
		typedef std::vector<UString> UStringList;
	public:
		FileList(void);

		UString				GetBasePath(void);
		int					GetNumFiles(void);
		UString				GetFile(size_t index);
		const UStringList&  GetList(void) const;

	private:
		UString		 m_basePath;
		UStringList  m_list;
	};

	class VIX_API FileSystem
	{
		typedef std::vector<UString> FileList;
	public:
		FileSystem(void);

		~FileSystem(void);

		void Init(void);
		void Restart(void);
		void Shutdown(void);

	private:
		size_t	m_readCnt; //bytes read
		size_t	m_loadCnt; //files read
		UString	m_folder;  //game folder

	};

}

#endif
