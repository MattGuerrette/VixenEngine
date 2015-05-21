#include <vix_fltk.h>

namespace Vixen {

	void FLTK_CenterWindow(Fl_Window* window)
	{
		if (window) {
			int x = (Fl::w() - window->w()) / 2;
			int y = (Fl::h() - window->h()) / 2;
			window->position(x, y);
		}
	}

}