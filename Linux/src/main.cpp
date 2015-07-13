
#include <vix_debugutil.h>
#include <vix_filemanager.h>
#include <vix_file.h>
#include <vix_osutil.h>
#include <vix_game.h>
#include <vix_model.h>
#include <vix_freeimage.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>

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
    GLTexture*  m_tex;

};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    //Initialize the resource manager;
    PathManager::instance().Initialize();
    ResourceManager::instance().OpenResource(VTEXT("floor.jpg"), ResourceType::Texture);

    File* file = ResourceManager::instance().AccessResource(VTEXT("floor.jpg"), ResourceType::Texture);
    FREEIMAGE_BMP* bmp = FREEIMAGE_LoadImage(file);
    m_tex = new GLTexture(bmp);

    DebugPrintF(VTEXT("Total Open Files: %i\nTotal Bytes Open: %i"),
                FileManager::instance().TotalFilesOpen(),
                FileManager::instance().TotalBytesOpen());
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
    if(m_tex)
        GLRENDERER->Render2DTexture(m_tex, Vector2(20, 20), Rect::EMPTY, Vector2(0,0), Vector2(1,1),
                                0.0f, 1.0f, Colors::White, 0.0f);

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

}

int main(int argc, char* argv[])
{
    //DebugPrintF(os_exec_dir().c_str());
    //TestGame game;

    //return game.Run();

    PathManager::instance().Initialize();
    ResourceManager::instance().OpenResource(VTEXT("floor.jpg"), ResourceType::Texture);

    DebugPrintF(VTEXT("Total Open Files: %i\nTotal Bytes Open: %i"),
                FileManager::instance().TotalFilesOpen(),
                FileManager::instance().TotalBytesOpen());

    return 0;
}
