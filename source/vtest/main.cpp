
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_font.h>

using namespace Vixen;

class TestGame : public IGame
{
public:
    TestGame();

    void VOnStartup();
    void VOnShutdown();
    void VOnUpdate(float dt);
    void VOnRender(float dt);

private:
    ICamera3D*  camera3D;
    IModel*     model;
    IModel*     floor;
    IFont*      font;
    ITexture*   croissant;
    Transform   modelTransform;
    Transform   floorTransform;
    Transform   croissantTransform;
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    

    m_renderer->VSetClearColor(Vixen::Colors::CornflowerBlue);

    camera3D = m_renderer->Camera3D();
    camera3D->VSetSpeed(500.0f);

    croissant = ResourceManager::OpenTexture(VTEXT("transparent.png"));

    model = ResourceManager::OpenModel(VTEXT("raptor.mdl"));
    floor = ResourceManager::OpenModel(VTEXT("floor.mdl"));
    font = ResourceManager::OpenFont(VTEXT("Consolas_24.fnt"));
    modelTransform = Transform( 0.0f, 0.0f, 5.0f,
                                0.0f, 0.0f, 0.0f,
									1.f, 1.f, 1.f);
    floorTransform = Transform(0.0f, -5.0f, 5.0f,
        0.0f, 0.0f, 0.0f,
        10.0f, 10.0f, 10.0f);
    croissantTransform = Transform(20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    model->VSetTransform(&modelTransform);
    floor->VSetTransform(&floorTransform);

    m_window->VToggleCursor();
}

void TestGame::VOnUpdate(float dt)
{
    //modelTransform.RotateY(dt);

    if (m_keyboard->SingleKeyPress(IKEY::F2))
        m_window->VClose();

    if (m_keyboard->KeyPress(IKEY::S))
        camera3D->VWalk(-dt);

    if (m_keyboard->KeyPress(IKEY::W))
        camera3D->VWalk(dt);

    if (m_keyboard->KeyPress(IKEY::A))
        camera3D->VStrafe(-dt);

    if (m_keyboard->KeyPress(IKEY::D))
        camera3D->VStrafe(dt);
       

    int deltaX = m_mouse->DeltaX(m_window->VGetClientBounds().w / 2);
    int deltaY = m_mouse->DeltaY(m_window->VGetClientBounds().h / 2);
    camera3D->VRotateX(deltaY * 0.25f);
    camera3D->VRotateY(deltaX * 0.25f);

    camera3D->VUpdate(dt);

    m_window->VTrapCursorCenter();
}

void TestGame::VOnRender(float dt)
{
    
    m_renderer->VRenderModel(model);
    m_renderer->VRenderModel(floor);


    //ALL 2D UI IS DRAW AFTER SCENE IS DRAWN
    USStream ss;
    ss << "FPS: " << m_window->VFPS();
    m_renderer->VRenderText2D(font, ss.str(), croissantTransform);
}

void TestGame::VOnShutdown()
{
    delete font;
    delete croissant;
    delete model;
    delete floor;
}

int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}