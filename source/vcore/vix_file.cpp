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

#include <vix_file.h>
#include <vix_fileutil.h>
#include <cstring>
#include <cerrno>

#ifdef VIX_SYS_LINUX
	#include <sys/stat.h>
#endif


namespace Vixen {

	File::File()
		: IFile()
	{
		m_position = 0;
		m_size = 0;
	}

	File::~File()
	{
		Close();
	}


	bool File::Open(UString path)
	{
		m_filePath = os_path(path);
		m_fileName = getFileName(m_filePath);
		m_baseName = getFileName(m_filePath, false);

		m_handle = fopen(m_filePath.c_str(), "rb");
		if(!m_handle) {
			m_error = FileError::Open;
			PError();
			return false;
		}

		return true;
	}

	bool File::Close()
	{
		int ret = 0;
		//Close file if handle still active
		if(m_handle)
		{
			ret = fclose(m_handle);
			m_handle = NULL;
		}

		return (ret < 0) ? false : true;
	}

	bool File::Flush()
	{
		return false;
	}

	void File::Read(BYTE* out, size_t len)
	{
		fread(out, sizeof(char), len, m_handle);
	}

	bool File::Seek(size_t pos, FileSeek mode)
	{
		if(!m_handle)
			return false;

		int ret = 0;
		switch(mode)
		{
			case FileSeek::Set:
			{
				ret = fseek(m_handle, pos, SEEK_SET);
			} break;

			case FileSeek::Current:
			{
				ret = fseek(m_handle, pos, SEEK_CUR);
			} break;

			case FileSeek::End:
			{
				ret = fseek(m_handle, pos, SEEK_END);
			} break;
		}

		m_position = Tell();

		return (ret != 0) ? false : true;
	}

	bool File::PError(int err /* = 0 */)
	{
		DebugPrintF(VTEXT("FileError: %s"), strerror(errno));
		return (err < 0) ? true : false;
	}

	size_t File::Tell()
	{
		return ftell(m_handle);
	}

	size_t File::Position()
	{
		return m_position;
	}

	size_t File::SizeBytes()
	{
		//Need to grab size from stat struct in order to allow for
		//files > 2GB in size
		struct stat st;
		stat(m_filePath.c_str(), &st);
		m_size = st.st_size;

		return m_size;
	}

	size_t File::SizeKBytes()
	{
		return SizeBytes() / 1024;
	}

	FileError File::Error()
	{
		return m_error;
	}

	UString File::BaseName()
	{
		return m_baseName;
	}

	UString File::FileName()
	{
		return m_fileName;
	}

	UString File::FilePath()
	{
		return m_filePath;
	}

	FILE* File::Handle()
	{
		return m_handle;
	}


}
