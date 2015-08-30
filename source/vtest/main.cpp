
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_dxtexture.h>
#include <vix_dxrenderer.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <dxgidebug.h>

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
    ITexture* tex;
    IShader*  vShader;
    IShader*  pShader;
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    FileManager::Initialize();
    PathManager::Initialize();

    m_renderer->VSetClearColor(Vixen::Colors::CornflowerBlue);

    //tex = ResourceManager::OpenTexture(VTEXT("croissant.png"));
    vShader = ResourceManager::OpenShader(VTEXT("VertexShader.hlsl"), ShaderType::VERTEX_SHADER);
    pShader = ResourceManager::OpenShader(VTEXT("PixelShader.hlsl"), ShaderType::PIXEL_SHADER);

    FileManager::PrintOpen();
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
    
}

void TestGame::VOnShutdown()
{
    //delete tex;
    delete vShader;
    delete pShader;
}

int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}