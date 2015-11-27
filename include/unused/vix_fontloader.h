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

#ifndef VIX_FONTLOADER_H
#define VIX_FONTLOADER_H

#include <vix_platform.h>
#include <vix_stlutil.h>
#include <vix_bmfont.h>
#include <atomic>
#include <thread>

namespace Vixen {

	class VIX_API FontLoader
	{
	public:
		FontLoader();

		/**
		*	Starts dedicated Font loading thread.
		*/
		void Load();

		/**
		*	Returns true if FontLoader is done loading fonts.
		*/
		const std::atomic<bool>& IsFinished();

		BMFont* GetFont();

	private:
		std::vector<BMFont*>  m_fonts;
		BMFont*               m_font;
		atomic_bool     	  m_finished;
	};

}

#endif
