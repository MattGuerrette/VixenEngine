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
