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

#ifndef VIX_FLTK_H
#define VIX_FLTK_H

/*FLTK INCLUDES*/
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>

/*VIXEN INCLUDES*/
#include <vix_platform.h>

namespace Vixen {

	/*CENTERS FL_WINDOW ON SCREEN*/
	VIX_API
	void FLTK_CenterWindow(Fl_Window* window);


}

#endif
