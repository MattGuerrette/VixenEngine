#ifndef VIX_CONFIGAPP_H
#define VIX_CONFIGAPP_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_fltk.h>

namespace Vixen {

	class VIX_API ConfigApp
	{
		/*CONSTANTS*/

		static const int     WIDTH;
		static const int     HEIGHT;
		static const UString TITLE;

	public:
		ConfigApp();

		~ConfigApp();

		void Init();
		void Run(int argc, char** argv);


	private:
		void create_child_widgets();

	private:
		Fl_Window* m_window;
		Fl_Image*  m_image;
	};

}

#endif
