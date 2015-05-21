#include <vix_zlib.h>

void 
ZLIB_Error(int error_code)
{

}

FILE*
ZLIB_OpenFile(const char* zipPath, const char* file)
{
	if (!zipPath || !file)
		return NULL;

	unzFile uf;
	uf = unzOpen64(zipPath);

	if (uf)
	{
		unz_global_info64 gi;
		int err;
		err = unzGetGlobalInfo64(uf, &gi);
		if (err != UNZ_OK)
			printf("Error %d with zipfile in unzGetGlobalInfo\n", err);

		for (int i = 0; i < gi.number_entry; i++) {
			unz_file_info64 fi;
			char filename[256];
			err = unzGetCurrentFileInfo64(uf, &fi, filename, sizeof(filename), NULL, 0, NULL, 0);
			if (err != UNZ_OK) {
				printf("error %d in unzGetCurrentFileInfo64\n");
				break;
			}

			if (strcmp(file, filename) == 0)
			{
				/*create temp file*/
			}

		}
	}

	return NULL;
}

BYTE*
ZLIB_OpenRaw(const char* zipPath, const char* file)
{
	if (!zipPath || !file)
		return NULL;

	unzFile uf;
	
	uf = unzOpen64(zipPath);

	if (uf)
	{
		unz_global_info64 gi;
		int err;
		err = unzGetGlobalInfo64(uf, &gi);
		if (err != UNZ_OK)
			printf("Error %d with zipfile in unzGetGlobalInfo\n", err);

		for (int i = 0; i < gi.number_entry; i++) {
			unz_file_info64 fi;
			char filename[256];
			err = unzGetCurrentFileInfo64(uf, &fi, filename, sizeof(filename), NULL, 0, NULL, 0);
			if (err != UNZ_OK) {
				printf("error %d in unzGetCurrentFileInfo64\n");
				break;
			}

			if (strcmp(file, filename) == 0)
			{
				/*read raw data*/
				unzOpenCurrentFile(uf);
				BYTE* raw_data = new BYTE[ZIPBUFSIZE+1];
				int err = unzReadCurrentFile(uf, raw_data, ZIPBUFSIZE);
				if (err < 0)
					printf("Error reading png file");
				unzCloseCurrentFile(uf);
				unzClose(uf);
				return (BYTE*)raw_data;
			}

			

			printf("%d Name: %s\n", i, filename);
			if((i+1) < gi.number_entry)
				err = unzGoToNextFile(uf);
			if (err != UNZ_OK) {
				printf("error %d in unzGoToNextFile\n");
				break;
			}

			
		}
	}

	return NULL;
}

int
ZLIB_NumFiles(const char* zipPath)
{
	return 0;
}