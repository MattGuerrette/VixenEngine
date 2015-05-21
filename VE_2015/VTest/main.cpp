
#include <vix_game.h>
#include <vix_fontloader.h>

using namespace Vixen;

#define GLRENDERER ((GLRenderer*)m_renderer)

class TestGame : public IGame
{
public:
	TestGame();

	void VOnStartup() override;
	void VOnUpdate(float dt) override;
	void VOnRender(float dt) override;
	void VOnShutdown() override;

private:
	BMFont* m_font;
	FontLoader fontLoader;
};

TestGame::TestGame()
	: IGame()
{

}

void TestGame::VOnStartup()
{
	//Non-threaded loading
	//m_font = m_content.LoadFont(VTEXT("HanWan_24.fnt"));

	//Threaded loading
	fontLoader.Load();
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
	
	if (fontLoader.IsFinished()) {
		BMFont* font = fontLoader.GetFont();
		if(font)
			GLRENDERER->Render2DText(font, VTEXT("VE"), Vector2(20, 20), 1.0f, Colors::White);
	}
	
	
	//GLRENDERER->Render2DText(m_font, VTEXT("你好"), Vector2(20, 20), 1.0f, Colors::White);
}

void TestGame::VOnShutdown()
{

}

int main(int argc, char* argv[])
{
	TestGame test;

	return test.Run();
}