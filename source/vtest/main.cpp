
#include <vix_game.h>

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
   
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    m_renderer->VSetClearColor(Vixen::Colors::CornflowerBlue);
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
   
}

void TestGame::VOnShutdown()
{
   
}


int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}