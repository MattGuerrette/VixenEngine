#include <vix_configapp.h>

namespace Vixen {

	const int     ConfigApp::WIDTH  = 500;
	const int     ConfigApp::HEIGHT = 500;

	ConfigApp::ConfigApp()
	{

	}

	ConfigApp::~ConfigApp()
	{

	}

	void ConfigApp::Init()
	{
		Fl::scheme("plastic");
		m_window = new Fl_Window(WIDTH, HEIGHT, "Configuration");
		FLTK_CenterWindow(m_window);
		create_child_widgets();
		m_window->end();
	}

	void ConfigApp::Run(int argc, char** argv)
	{
		m_window->show(argc, argv);
		
		Fl::run();
	}

	void ConfigApp::create_child_widgets()
	{
		int TAB_X = 20;
		int TAB_Y = 200;
		/*create tab widget*/
		Fl_Tabs* tab_widget = new Fl_Tabs(TAB_X, TAB_Y, WIDTH - 40, HEIGHT - 220);
		{
			/*create graphics tab*/
			Fl_Group* gfx_conf_tab = new Fl_Group(TAB_X, TAB_Y + 15, WIDTH - 40, HEIGHT - 200, "Graphics");
			{
				/*populate gfx tab*/
				Fl_Choice* choice = new Fl_Choice(TAB_X + 120, TAB_Y + 50, 150, 25, "Resolution: ");
			}
			gfx_conf_tab->end();

			///*create input tab*/
			//Fl_Group* input_conf_tab = new Fl_Group(TAB_X, TAB_Y + 15, WIDTH - 40, HEIGHT - 45, "Input");
			//{

			//}
			//input_conf_tab->end();
		}
		tab_widget->end();
	}

}