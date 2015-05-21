#include <vix_config.h>
#include <vix_tinyxml.h>
#include <vix_debugutil.h>

namespace Vixen {

	ConfigSettings::ConfigSettings()
	{
		m_ApplicationX = 0;
		m_ApplicationY = 0;
		m_ApplicationW = 0;
		m_ApplicationH = 0;
	}

	ConfigSettings::~ConfigSettings()
	{

	}

	ErrCode ConfigSettings::Serialize(const ConfigSettings& settings)
	{
		/*output to file*/
		XMLDOC   document;
		FILE*    fp = NULL;
		fopen_s(&fp, "config_settings.xml", "w+");
		if (!fp) {
			DebugPrintF(VTEXT("Failed to write to config file: %s\n"),
				ErrCodeString(ErrCode::ERR_XML_WRITE_FAIL));
			return ErrCode::ERR_XML_WRITE_FAIL;
		}
		ConfigSettings _settings = settings;
		XMLPRINT printer(fp);
		printer.OpenElement("APP-SETTINGS");
		write_gfx_settings(printer, _settings);
		write_input_settings(printer, _settings);
		printer.CloseElement();
		
		document.Print(&printer);
		return ErrCode::ERR_SUCCESS;
	}

	ErrCode ConfigSettings::Deserialize(ConfigSettings& settings)
	{
		return ErrCode::ERR_SUCCESS;
	}

	void ConfigSettings::write_gfx_settings(XMLPRINT& printer, ConfigSettings & settings)
	{
		printer.OpenElement("GFX-SETTINGS");
		printer.PushAttribute("CLIENT_X", settings.m_ApplicationX);
		printer.PushAttribute("CLIENT_Y", settings.m_ApplicationY);
		printer.PushAttribute("CLIENT_WIDTH", settings.m_ApplicationW);
		printer.PushAttribute("CLIENT_HEIGHT", settings.m_ApplicationH);
		printer.CloseElement();
	}

	void ConfigSettings::write_input_settings(XMLPRINT& printer, ConfigSettings & settings)
	{

	}
}