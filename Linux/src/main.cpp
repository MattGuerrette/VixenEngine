
#include <vix_debugutil.h>
#include <vix_filemanager.h>
#include <vix_file.h>
#include <vix_osutil.h>
#include <vix_game.h>
#include <vix_model.h>
#include <vix_freeimage.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_bmfont.h>
#include <vix_libarchive.h>

using namespace Vixen;

#define GLRENDERER ((GLRenderer*)m_renderer)

class TestGame : public IGame
{
public:
    TestGame();

    void VOnStartup();
    void VOnShutdown();
    void VOnUpdate(float dt);
    void VOnRender(float dt);

private:
    //GLTexture*  m_tex;
    BMFont*     m_font;
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    m_font = NULL;
    //m_tex = NULL;

    PathManager::Initialize();
    ResourceManager::OpenResource(VTEXT("floor.jpg"), ResourceType::Texture);
    ResourceManager::OpenResource(VTEXT("Consolas_24.fnt"), ResourceType::Font);

    File* file = ResourceManager::AccessResource(VTEXT("Consolas_24.fnt"), ResourceType::Font);
    m_font = new BMFont(file);
    m_font->Load();

    DebugPrintF(VTEXT("Total Open Files: %i\nTotal Bytes Open: %i\n"),
                FileManager::TotalFilesOpen(),
                FileManager::TotalBytesOpen());
    FileManager::PrintOpen();
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
    /*if(m_tex)
        GLRENDERER->Render2DTexture(m_tex, Vector2(20, 20), Rect::EMPTY, Vector2(0,0), Vector2(1,1),
                                0.0f, 1.0f, Colors::White, 0.0f);

    */

    /*if(m_font->IsLoaded()) {
        m_font->InitTextures();
    }

    if(m_font->IsInitialized())
    {
        Rect r = m_window->VGetClientBounds();
    	USStream fps;
    	fps << "FPS: " << ((SDLGameWindow*)m_window)->Timer()->FPS();
    	GLRENDERER->Render2DText(m_font, fps.str(), Vector2(r.w-150.0f, 20), 1.0f, Colors::White);
    }*/

    /*if(m_fontLoader.IsFinished())
    {
        BMFont* m_font = m_fontLoader.GetFont();

        //Test File IO
        m_file->Seek(0, FileSeek::End);
        USStream ss;
        ss << "Position: " << m_file->Position() << "\n";
        ss << "File Path: " << m_file->FilePath() << "\n";
        ss << "File Name: " << m_file->FileName() << "\n";
        ss << "File BaseName: " << m_file->BaseName() << "\n";
        ss << "File SizeBytes: " << m_file->SizeBytes() << "B\n";
        ss << "File SizeKBytes: " << m_file->SizeKBytes() << "KB\n";

        GLRENDERER->Render2DText(m_font, ss.str(), Vector2(20, 20), 1.0f, Colors::White);

    	Rect r = m_window->VGetClientBounds();
    	USStream fps;
    	fps << "FPS: " << ((SDLGameWindow*)m_window)->Timer()->FPS();
    	GLRENDERER->Render2DText(m_font, fps.str(), Vector2(r.w-150.0f, 20), 1.0f, Colors::White);

    }*/
}

void TestGame::VOnShutdown()
{
    delete m_font;
    m_renderer->VShutDown();
    delete m_renderer;
}

int main(int argc, char* argv[])
{
    //TestGame game;

    //return game.Run();

    const char* FILES[3] =
    {
        "croissant.png",
        "firefox.jpg",
        NULL
    };

    ARCHIVE_Write("test.tar.gz", FILES);

    FileManager::PrintOpen();

    return 0;
}
