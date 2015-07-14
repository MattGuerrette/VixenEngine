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
	struct stat st;

	a = archive_write_new();
	archive_write_add_filter_gzip(a);
	archive_write_set_format_pax_restricted(a);
	archive_write_open_filename(a, outname);

	Vixen::File* file = NULL;
	while(*paths)
	{
		Vixen::FileManager::OpenFile(*paths);
		file = Vixen::FileManager::AccessFile(*paths);
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

		Vixen::FileManager::CloseFile(*paths);
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
