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


#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "vix_filemanager.h"
#include "vix_inireader.h"
#include "vix_iniwriter.h"
#include "vix_debugutil.h"
#include "vix_game.h"

using namespace Vixen;

#ifdef _WIN32
int
WinMain (_In_ HINSTANCE hInstance,
         _In_opt_ HINSTANCE hPrevInstance,
         _In_ LPSTR lpCmdLine,
         _In_ int nShowCmd)
#else
int
main (int argc, char *argv[])
#endif
{
    Vixen::Game _game;


    return _game.Run();
}
