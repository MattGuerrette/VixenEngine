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

#include <vix_libarchive.h>
#include <vix_debugutil.h>
#include <vix_filemanager.h>
#include <cstring>

void
ARCHIVE_Extract(char* zip, char* file, BYTE* buffer)
{
	archive* a;
	archive* ext;
	archive_entry* entry;
	int ret;
	a = archive_read_new();
	archive_read_support_format_zip(a);
	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM);

	if ((ret = archive_read_open_filename(a, zip, LARGE_BUFSIZE)))
		Vixen::DebugPrintF(VTEXT("err: archive_read_open_filename %s \n"),
		        archive_error_string(a));
	for (;;) {
		ret = archive_read_next_header(a, &entry);
		if (ret == ARCHIVE_EOF)
			break;
		/*look for requested file*/
		const char* entryName = archive_entry_pathname(entry);
		if (strcmp(file, entryName) == 0)
			break; /*if found, break*/
	}

	BYTE* buff = ARCHIVE_CopyData(a);
	memcpy(buffer, buff, LARGE_BUFSIZE);
	delete[] buff;
	buff = NULL;

	archive_read_close(a);
	archive_read_free(a);
}

void
ARCHIVE_Write(const char* outname, BYTE* data, size_t len)
{
	struct archive* a;
	struct archive_entry* entry;

	a = archive_write_new();
	archive_write_add_filter_gzip(a);
	archive_write_set_format_pax_restricted(a); // Note 1
	archive_write_open_filename(a, outname);

	entry = archive_entry_new(); // Note 2
	archive_entry_set_pathname(entry, "floor.jpg");
	archive_entry_set_size(entry, len); // Note 3
	archive_entry_set_filetype(entry, AE_IFREG);
	archive_entry_set_perm(entry, 0644);
	archive_write_header(a, entry);

	archive_write_data(a, data, len);




	archive_entry_free(entry);


	archive_write_close(a);
	archive_write_free(a);
}

void
ARCHIVE_Write(const char* outname, const char** paths)
{
	struct archive* a;
	struct archive_entry* entry;

	a = archive_write_new();
	archive_write_add_filter_gzip(a);
	archive_write_set_format_pax_restricted(a);
	archive_write_open_filename(a, outname);

	Vixen::File* file = NULL;
	while(*paths)
	{
		UString _path = Vixen::UStringFromCharArray(*paths);
		Vixen::FileManager::OpenFile(_path);
		file = Vixen::FileManager::AccessFile(_path);
		entry = archive_entry_new();
		archive_entry_set_pathname(entry, *paths);
		archive_entry_set_size(entry, file->SizeBytes());
		archive_entry_set_filetype(entry, AE_IFREG);
		archive_entry_set_perm(entry, 0644);
		archive_write_header(a, entry);

		char* buff = new char[file->SizeBytes()];
		file->Read((BYTE*)buff, file->SizeBytes());
		buff[file->SizeBytes()] = NULL;
		archive_write_data(a, buff, file->SizeBytes());
		delete[] buff;

		Vixen::FileManager::CloseFile(_path);
		archive_entry_free(entry);

		paths++;
	}

	archive_write_close(a);
	archive_write_free(a);
}

BYTE*
ARCHIVE_CopyData(archive* ar)
{
	BYTE* buff = new BYTE[LARGE_BUFSIZE];

	archive_read_data(ar, (void*)buff, LARGE_BUFSIZE);

	return buff;
}
