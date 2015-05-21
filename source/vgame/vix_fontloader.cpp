#include <vix_fontloader.h>
#include <vix_tinyxml.h>
#include <vix_paths.h>
#include <vix_gltexture.h>

namespace Vixen {

	FontLoader::FontLoader()
	{
		m_finished = false;
		m_font = nullptr;
	}

	const std::atomic<bool>& FontLoader::IsFinished()
	{
		return m_finished;
	}

	void FontLoader::Load()
	{
		//Start thread and detach to load font files
		//asynchronously.
		std::thread t([](std::vector<BMFont*>& fonts, BMFont* font, std::atomic<bool>* finished) {
			UString _path = FONT_FOLDER_PATH + VTEXT("HanWan_24.fnt");
			font = new BMFont(_path);
			fonts.push_back(font);

			UString _texPath = os_path(FONT_FOLDER_PATH + TEX_FOLDER_PATH);

			/*load textures for font*/
			for (auto& page : font->FontFile().pages) {
				//Texture* tex = new GLTexture(_texPath + page.file);
				//if (tex)
					//font->AddPageTexture(tex);
			}

			*finished = true;
		}, std::ref(m_fonts), m_font, &m_finished);
		t.detach();
	}

	BMFont* FontLoader::GetFont()
	{
		if (m_finished) {
			return m_fonts[0];
		}
	}

}