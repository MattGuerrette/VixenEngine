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