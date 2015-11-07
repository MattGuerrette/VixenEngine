#include <vix_game.h>
#include <vix_version.h>

int main(int argc, char* argv[])
{

    Vixen::DebugPrintF(VTEXT("VixenEngine\nVersion: %d.%d.%d\n"),
            VixenEngine_VERSION_MAJOR,
            VixenEngine_VERSION_MINOR,
            VixenEngine_VERSION_BUILD);


    Vixen::Game _game;

    return _game.Run();
}
