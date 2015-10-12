#include <vix_game.h>
#include <vix_version.h>
#include <vix_osutil.h>

using namespace Vixen;

class TestGame : public Game
{
public:
    TestGame();

    void VOnStartup();
    void VOnShutdown();
    void VOnUpdate();
    void VOnRender();

private:

};

TestGame::TestGame()
    : Game()
{

}

void TestGame::VOnStartup()
{

}

void TestGame::VOnUpdate()
{

}

void TestGame::VOnRender()
{

}

void TestGame::VOnShutdown()
{

}

int main(int argc, char* argv[])
{

    /*Vixen::DebugPrintF(VTEXT("VixenEngine\nVersion: %d.%d.%d"),
            VixenEngine_VERSION_MAJOR,
            VixenEngine_VERSION_MINOR,
            VixenEngine_VERSION_BUILD);
    Vixen::DebugPrintF(VTEXT("ExecPath: %s"), Vixen::os_exec_dir().c_str());*/

    TestGame _game;

    return _game.Run();
}
