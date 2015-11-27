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

#ifndef VIX_CONFIG_H
#define VIX_CONFIG_H

#include <vix_platform.h>
#include <vix_errglobals.h>
#include <vix_tinyxml.h>

namespace Vixen {

	typedef tinyxml2::XMLPrinter XMLPRINT;

	class VIX_API ConfigSettings
	{
	public:
		ConfigSettings();

		~ConfigSettings();

		static ErrCode Serialize(const ConfigSettings& settings);
		static ErrCode Deserialize(ConfigSettings& settings);

	private:
		static void write_gfx_settings(XMLPRINT& printer, ConfigSettings& settings);
		static void write_input_settings(XMLPRINT& printer, ConfigSettings& settings);

	private:
		int m_ApplicationX;
		int m_ApplicationY;
		int m_ApplicationW;
		int m_ApplicationH;
	};

}


#endif
