
#include <vix_game.h>

using namespace Vixen;

class TestGame : public Game
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
    : Game()
{

}

void TestGame::VOnStartup()
{

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
