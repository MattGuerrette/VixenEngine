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


	bool File::Open(std::string path, FileMode mode)
	{
		m_filePath = os_path(path);
		m_fileName = getFileName(m_filePath);
		m_baseName = getFileName(m_filePath, false);

        switch (mode)
        {
            case FileMode::ReadBinary:
            {
#ifdef VIX_SYS_WINDOWS
                fopen_s(&m_handle, m_filePath.c_str(), "rb");
#else
                m_handle = fopen(m_filePath.c_str(), "rb");
#endif
            } break;

            case FileMode::ReadText:
            {
#ifdef VIX_SYS_WINDOWS
                fopen_s(&m_handle, m_filePath.c_str(), "r");
#else
                m_handle = fopen(m_filePath.c_str(), "r");
#endif
            } break;

            case FileMode::WriteBinary:
            {
#ifdef VIX_SYS_WINDOWS
                fopen_s(&m_handle, m_filePath.c_str(), "wb");
#else
                m_handle = fopen(m_filePath.c_str(), "wb");
#endif
            } break;

            case FileMode::WriteText:
            {
#ifdef VIX_SYS_WINDOWS
                fopen_s(&m_handle, m_filePath.c_str(), "w");
#else
                m_handle = fopen(m_filePath.c_str(), "w");
#endif
            } break;

            case FileMode::AppendBinary:
            {
#ifdef VIX_SYS_WINDOWS
                fopen_s(&m_handle, m_filePath.c_str(), "ab");
#else
                m_handle = fopen(m_filePath.c_str(), "ab");
#endif
            } break;

            case FileMode::AppendText:
            {
#ifdef VIX_SYS_WINDOWS
                fopen_s(&m_handle, m_filePath.c_str(), "a");
#else
                m_handle = fopen(m_filePath.c_str(), "a");
#endif
            } break;

            default:
                break;
        }

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

	size_t File::Read(BYTE* out, size_t len)
	{
		size_t _len = 0;

		_len = fread(out, sizeof(BYTE), len, m_handle);

		return _len;
	}

    size_t File::Write(BYTE* in, size_t len)
    {
        size_t _len = 0;

        _len = fwrite(in, sizeof(BYTE), len, m_handle);

        return _len;
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
#ifdef VIX_SYS_WINDOWS
		char s_buffer[VIX_BUFSIZE];
		strerror_s(s_buffer, errno);
		DebugPrintF("FileError: %s", s_buffer);
#else
		DebugPrintF("FileError: %s", strerror(errno));
#endif
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

#ifdef VIX_SYS_LINUX
		//Need to grab size from stat struct in order to allow for
		//files > 2GB in size
		struct stat st;
		stat(m_filePath.c_str(), &st);
		m_size = st.st_size;
#else
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (!GetFileAttributesEx(m_filePath.c_str(), GetFileExInfoStandard, &fad))
			return -1;

		LARGE_INTEGER size;
		size.HighPart = fad.nFileSizeHigh;
		size.LowPart = fad.nFileSizeLow;

		m_size = static_cast<size_t>(size.QuadPart);
#endif

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

	std::string File::BaseName()
	{
		return m_baseName;
	}

	std::string File::FileName()
	{
		return m_fileName;
	}

	std::string File::FilePath()
	{
		return m_filePath;
	}

	FILE* File::Handle()
	{
		return m_handle;
	}


}
