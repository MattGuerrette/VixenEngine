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

#include <vix_freeimage.h>
#include <vix_fileutil.h>

namespace Vixen {

	FREE_IMAGE_FORMAT
	FREEIMAGE_FormatFromExtension(const UString& ext)
	{
		if (ext == VTEXT("png"))
			return FIF_PNG;
		if (ext == VTEXT("jpg"))
			return FIF_JPEG;
		if (ext == VTEXT("bmp"))
			return FIF_BMP;
		if (ext == VTEXT("tga"))
			return FIF_TARGA;

		return FIF_UNKNOWN;
	}

	void
	FREEIMAGE_LoadPNGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data)
	{
		if (!header || !raw_data)
			return;

		header->width = (raw_data[16] << 24) + (raw_data[17] << 16) + (raw_data[18] << 8) + (raw_data[19] << 0);
		header->height = (raw_data[20] << 24) + (raw_data[21] << 16) + (raw_data[22] << 8) + (raw_data[23] << 0);
		header->bitdepth = (raw_data[24]);
	}

	void
	FREEIMAGE_LoadJPGHeader(FREEIMAGE_HEADER* header, BYTE* raw_data)
	{
		if (!header || !raw_data)
			return;

		header->width = (raw_data[12] << 8) + (raw_data[13] << 0);
		header->height = (raw_data[14] << 8) + (raw_data[15] << 0);
	}

	void
	FREEIMAGE_LoadTGAHeader(FREEIMAGE_HEADER* header, BYTE* raw_data)
	{
		header->width = (raw_data[12] << 8) + (raw_data[13] << 0);
		header->height = (raw_data[14] << 8) + (raw_data[15] << 0);
	}

	FREEIMAGE_BMP*
	FREEIMAGE_LoadImage(const UString& filePath)
	{
		FREEIMAGE_BMP* vix_bmp = new FREEIMAGE_BMP;
		vix_bmp->path = filePath;
		vix_bmp->name = getFileName(filePath);
		vix_bmp->format = FREEIMAGE_FormatFromExtension(getFileExtension(filePath, false));
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;

		/*Here we must */

		//Check file signature and deduce format
#ifdef UNICODE
		vix_bmp->format = FreeImage_GetFileTypeU(filePath.c_str());
#else
		vix_bmp->format = FreeImage_GetFileType(filePath.c_str());
#endif
		if (vix_bmp->format == FIF_UNKNOWN) {
#ifdef UNICODE
			vix_bmp->format = FreeImage_GetFIFFromFilenameU(filePath.c_str());
#else
			vix_bmp->format = FreeImage_GetFIFFromFilename(filePath.c_str());
#endif
		}

		//if still unknown, return NULL;
		if (vix_bmp->format == FIF_UNKNOWN)
			return NULL;

		//Check if FreeImage has reading capabilities
		if (FreeImage_FIFSupportsReading(vix_bmp->format)) {
#ifdef UNICODE
			//read image into struct pointer
			vix_bmp->bitmap = FreeImage_LoadU(vix_bmp->format, filePath.c_str());
#else
			vix_bmp->bitmap = FreeImage_Load(vix_bmp->format, filePath.c_str());
#endif

		}

		//If image failed to load, return NULL
		if (!vix_bmp->bitmap)
			return NULL;

		FreeImage_FlipVertical(vix_bmp->bitmap);

		//Retrieve image data
		vix_bmp->data = FreeImage_GetBits(vix_bmp->bitmap);
		//Retrieve image width
		vix_bmp->header.width = FreeImage_GetWidth(vix_bmp->bitmap);
		//Retrieve image height
		vix_bmp->header.height = FreeImage_GetHeight(vix_bmp->bitmap);
		if (vix_bmp->data == 0 || vix_bmp->header.width == 0 || vix_bmp->header.height == 0)
			return NULL;

		//return bitmap
		return vix_bmp;
	}


	FREEIMAGE_BMP*
	FREEIMAGE_LoadImage(const UString& filePath, BYTE* raw_data, int len)
	{
		if (!raw_data)
			return NULL;

		FREEIMAGE_BMP* vix_bmp = new FREEIMAGE_BMP;
		vix_bmp->path = filePath;
		vix_bmp->name = getFileName(filePath);
		vix_bmp->format = FREEIMAGE_FormatFromExtension(getFileExtension(filePath, false));
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;
		switch (vix_bmp->format)
		{
		case FIF_PNG:
			FREEIMAGE_LoadPNGHeader(&vix_bmp->header, raw_data);
			break;
		case FIF_TARGA:
			FREEIMAGE_LoadTGAHeader(&vix_bmp->header, vix_bmp->data);
			break;

		case FIF_JPEG:
			FREEIMAGE_LoadJPGHeader(&vix_bmp->header, vix_bmp->data);
			break;
		}


		//Check if FreeImage has reading capabilities
		if (FreeImage_FIFSupportsReading(vix_bmp->format)) {

			int pitch = ((vix_bmp->header.bitdepth * vix_bmp->header.width + 31) / 32) * 4;
			vix_bmp->bitmap = FreeImage_ConvertFromRawBits(raw_data,
				                                           vix_bmp->header.width,
				                                           vix_bmp->header.height,
														   pitch,
														   vix_bmp->header.bitdepth * 4, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		}

		//If image failed to load, return NULL
		if (!vix_bmp->bitmap)
			return NULL;

		FreeImage_FlipVertical(vix_bmp->bitmap);

		//return bitmap
		return vix_bmp;
	}


	void ReadFile(void *buffer, unsigned size, unsigned count, fi_handle handle)
	{
		fread(buffer, size, count, (FILE*)handle);
	}

	void SeekFile(fi_handle handle, long offset, int origin)
	{
		fseek((FILE*)handle, offset, origin);
	}

	void TellFile(fi_handle handle)
	{
		ftell((FILE*)handle);
	}

	FREEIMAGE_BMP*
	FREEIMAGE_LoadImage(File* file)
	{
		FREEIMAGE_BMP* vix_bmp = new FREEIMAGE_BMP;
		vix_bmp->path = file->FilePath();
		vix_bmp->name = file->FileName();
		vix_bmp->format = FREEIMAGE_FormatFromExtension(getFileExtension(file->FilePath(), false));
		vix_bmp->data = NULL;
		vix_bmp->bitmap = NULL;

		FreeImageIO io;
		io.read_proc = reinterpret_cast<FI_ReadProc>(&ReadFile);
		io.write_proc = NULL;
		io.seek_proc = reinterpret_cast<FI_SeekProc>(&SeekFile);
		io.tell_proc = reinterpret_cast<FI_TellProc>(&TellFile);

		vix_bmp->bitmap = FreeImage_LoadFromHandle(vix_bmp->format, &io, (fi_handle)file->Handle(), NULL);
		if(!vix_bmp->bitmap)
			DebugPrintF(VTEXT("Load bitmap failed\n"));

		//If image failed to load, return NULL
		if (!vix_bmp->bitmap)
			return NULL;


        //Grab bits per pixel
        vix_bmp->bpp = FreeImage_GetBPP(vix_bmp->bitmap);
        if (vix_bmp->bpp == 24) //If 24 bits, convert to 32 for engine use.
        {
            vix_bmp->bitmap = FreeImage_ConvertTo32Bits(vix_bmp->bitmap);
            vix_bmp->bpp = FreeImage_GetBPP(vix_bmp->bitmap);
        }

		//Flip image Y
		FreeImage_FlipVertical(vix_bmp->bitmap);

		//Retrieve image data
		vix_bmp->data = FreeImage_GetBits(vix_bmp->bitmap);
		//Retrieve image width
		vix_bmp->header.width = FreeImage_GetWidth(vix_bmp->bitmap);
		//Retrieve image height
		vix_bmp->header.height = FreeImage_GetHeight(vix_bmp->bitmap);

		//return bitmap
		return vix_bmp;
	}



}
