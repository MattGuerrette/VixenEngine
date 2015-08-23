#include <vix_freetypeengine.h>
#include <vix_debugutil.h>
#include <vix_freeimage.h>

namespace Vixen {

    FreeTypeEngine::FreeTypeEngine()
    {

    }



    bool FreeTypeEngine::Initialize()
    {
        FT_Error error;

        error = FT_Init_FreeType(&m_library);
        if (error)
        {
            DebugPrintF(VTEXT("FreeType Engine failed to initialize library."));
            return false;
        }

        FT_Face face;

        error = FT_New_Face(m_library,
            "C:\\Windows\\Fonts\\arial.ttf",
            0,
            &face);
        if (error == FT_Err_Unknown_File_Format)
        {
            DebugPrintF(VTEXT("Font could not be opened or read, and font format is unsupported."));
            return false;
        }
        else if (error)
        {
            DebugPrintF(VTEXT("Font could not be opened or read"));
            return false;
        }

        error = FT_Set_Char_Size(face, 12 * 64, 0,
            100, 0);
        if (error)
        {
            DebugPrintF(VTEXT("Font char size could not be set"));
            return false;
        }

        FT_Matrix     matrix;                 /* transformation matrix */
        FT_Vector     pen;                    /* untransformed origin  */

                                              /* set up matrix */
        matrix.xx = (FT_Fixed)(cos(0) * 0x10000L);
        matrix.xy = (FT_Fixed)(-sin(0) * 0x10000L);
        matrix.yx = (FT_Fixed)(sin(0) * 0x10000L);
        matrix.yy = (FT_Fixed)(cos(0) * 0x10000L);
      
        const char* _text = "ABCDEFGH";
        int width_ = 0;
        int height_ = 0;
        int num_chars = strlen(_text);
        width_ = 512;
        height_ = 512;

        pen.x = 0;
        pen.y = 0;

        for (int c = 0; c < num_chars; c++) {

            /* set transformation */
            FT_Set_Transform(face, &matrix, &pen);

            error = FT_Load_Char(face, _text[c], FT_LOAD_RENDER);

            if (error) {
                std::cout << "Error: Could not load char \"" << _text[c] << "\"" << std::endl;
                continue;
            }

            FT_Int x = face->glyph->bitmap_left;
            FT_Int y = height_ - face->glyph->bitmap_top;

            DrawStuff(&face->glyph->bitmap, x, y);

           
            pen.x += face->glyph->advance.x;
            pen.y += face->glyph->advance.y;
        }

        ShowImage();
      
        FT_Done_Face(face);
        FT_Done_FreeType(m_library);

        return true;
    }

    void FreeTypeEngine::DrawBitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y)
    {
        FT_Int  i, j, p, q;
        FT_Int  x_max = x + bitmap->width;
        FT_Int  y_max = y + bitmap->rows;


        for (i = x, p = 0; i < x_max; i++, p++)
        {
            for (j = y, q = 0; j < y_max; j++, q++)
            {
                if (i < 0 || j < 0 ||
                    i >= 512 || j >= 512)
                    continue;

                image[j][i] |= bitmap->buffer[q * bitmap->width + p];
            }
        }
    }

    
    void FreeTypeEngine::ShowImage(void)
    {
        int  i, j;


        FreeImage_Initialise();


        FIBITMAP* bitmap = FreeImage_Allocate(512, 512, 24);
        RGBQUAD color;
        color.rgbBlue = 255;
        color.rgbGreen = 255;
        color.rgbRed = 255;
        RGBQUAD gray;
        gray.rgbBlue = 128;
        gray.rgbGreen = 128;
        gray.rgbRed = 128;
        for (i = 0; i < 512; i++)
        {
            for (j = 0; j < 512; j++)
            {
                FreeImage_SetPixelIndex(bitmap, j, i, (BYTE*)image[i][j]);
                if (image[i][j] != 0)
                    FreeImage_SetPixelColor(bitmap, j, i, &color);
                if (image[i][j] < 128)
                    FreeImage_SetPixelColor(bitmap, j, i, &gray);

                /*putchar(image[i][j] == 0 ? ' '
                : image[i][j] < 128 ? '+'
                : '*');*/
            }

            //putchar('\n');
        }

        FreeImage_Save(FIF_PNG, bitmap, "test_char.png");

        FreeImage_DeInitialise();
    }

}