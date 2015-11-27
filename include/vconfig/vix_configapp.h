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
