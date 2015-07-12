
#include <vix_debugutil.h>
#include <vix_file.h>
#include <vix_osutil.h>
#include <vix_game.h>
#include <vix_fontloader.h>
#include <vix_model.h>
#include <vix_freeimage.h>
#include <FPSController.h>

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
    FontLoader m_fontLoader;
    FPSController* m_controller;
    Model*     m_model;
    GLTexture*  m_tex;
    bool       m_trap;

    //FILE I/O Stuff

    File m_file;
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    m_fontLoader.Load();

    m_model = new Model;
    m_model->InitFromFile(VTEXT("Models/floor.obj"));
    m_model->SetPosition(Vec3(0.0f, 0.0f, 0.0f));

    m_controller = new FPSController(m_keyboard, GLRENDERER->Camera3D());

    GLRENDERER->Camera3D()->SetPosition(Vec3(0.0f, 4.0f, 0.0f));

    m_window->VToggleCursor();

    m_trap = true;

    m_file.Open(VTEXT("/home/debunez/Development/VixenEngine/Linux/Textures/stackedTileSheet.png"));
    FREEIMAGE_BMP* bmp = Vixen::FREEIMAGE_LoadImage(&m_file);
    m_tex = new GLTexture(bmp);
}

void TestGame::VOnUpdate(float dt)
{
    static bool fs = false;
    if(m_keyboard->SingleKeyPress(IKEY::F1)) {
        fs = !fs;
        m_window->VSetFullscreen(fs);
    }
    if(m_keyboard->SingleKeyPress(IKEY::F2)) {
        m_window->VClose();
    }
    if(m_keyboard->SingleKeyPress(IKEY::F3)) {
        m_window->VToggleCursor();
    }
    if(m_keyboard->SingleKeyPress(IKEY::F4)) {
        m_trap = !m_trap;
    }


    if(!m_trap)
        return;

    if(m_keyboard->SingleKeyPress(IKEY::F5))
       GLRENDERER->Camera3D()->SetType(C3D_TYPE::FIRST_PERSON);
    if(m_keyboard->SingleKeyPress(IKEY::F6))
       GLRENDERER->Camera3D()->SetType(C3D_TYPE::FREEFORM);


      m_controller->Update(dt);


      int deltaX = m_mouse->DeltaX(m_window->VGetClientBounds().w/2);
      int deltaY = m_mouse->DeltaY(m_window->VGetClientBounds().h/2);
      GLRENDERER->Camera3D()->RotateY(deltaX * dt * 50.0f);
      GLRENDERER->Camera3D()->RotateX(-deltaY * dt * 50.0f);

      GLRENDERER->Camera3D()->Update(dt);

      if(m_trap)
        m_window->VTrapCursorCenter();
}

void TestGame::VOnRender(float dt)
{
    m_model->Render(GLRENDERER->Camera3D());

    GLRENDERER->Render2DTexture(m_tex, Vector2(20, 300), Rect::EMPTY, Vector2(0,0), Vector2(1,1),
                                0.0f, 1.0f, Colors::White, 0.0f);

    if(m_fontLoader.IsFinished())
    {
        BMFont* m_font = m_fontLoader.GetFont();

        //Test File IO
        m_file.Seek(0, FileSeek::End);
        USStream ss;
        ss << "Position: " << m_file.Position() << "\n";
        ss << "File Path: " << m_file.FilePath() << "\n";
        ss << "File Name: " << m_file.FileName() << "\n";
        ss << "File BaseName: " << m_file.BaseName() << "\n";
        ss << "File SizeBytes: " << m_file.SizeBytes() << "B\n";
        ss << "File SizeKBytes: " << m_file.SizeKBytes() << "KB\n";

        GLRENDERER->Render2DText(m_font, ss.str(), Vector2(20, 20), 1.0f, Colors::White);

        //CAMERA DEBUG STATISTICS
    	/*USStream ss;
    	ss << GLRENDERER->Camera3D()->Position().x << " : " << GLRENDERER->Camera3D()->Position().y << " : "
    		<< GLRENDERER->Camera3D()->Position().z << " : " << GLRENDERER->Camera3D()->Yaw() << " : " <<
    		GLRENDERER->Camera3D()->Pitch();
    	if(GLRENDERER->Camera3D()->GetType() == C3D_TYPE::FIRST_PERSON)
    		ss << "\n" << "First Person";
    	else
    		ss << "\n" << "Free Form";
            ss << "\n";
            ss << "Controls: " << "\n" << "F1: Toggle Fullscreen" << "\n" << "F2: Exit" << "\n"
               << "F3: Pause" << "\n" << "F4: Play Music" << "\n" << "F5: FPS Controls" << "\n" <<
               "F6: Free Controls" << "\n" << "WASD: Move Camera";

    	GLRENDERER->Render2DText(m_font, ss.str(), Vector2(20, 20), 1.0f, Colors::White);*/


    	Rect r = m_window->VGetClientBounds();
    	USStream fps;
    	fps << "FPS: " << ((SDLGameWindow*)m_window)->Timer()->FPS();
    	GLRENDERER->Render2DText(m_font, fps.str(), Vector2(r.w-150.0f, 20), 1.0f, Colors::White);

    }
}

void TestGame::VOnShutdown()
{

}

int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}
