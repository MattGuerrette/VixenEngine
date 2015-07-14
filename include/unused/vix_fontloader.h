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
