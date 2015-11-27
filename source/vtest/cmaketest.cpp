/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

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
