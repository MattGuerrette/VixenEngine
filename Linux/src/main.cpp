
#include <vix_game.h>
#include <vix_fontloader.h>

using namespace Vixen;

class TestGame : public IGame
{
public:
  TestGame();

  void VOnStartup() override;
  void VOnUpdate(float dt) override;
  void VOnRender(float dt) override;
  void VOnShutdown() override;

private:
  FontLoader fontLoader;

};

TestGame::TestGame()
  : IGame()
{

}

void TestGame::VOnStartup()
{
  fontLoader.Load();
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
  if(fontLoader.IsFinished())
  {
      BMFont* font = fontLoader.GetFont();
      if(font)
	     ((GLRenderer*)m_renderer)->Render2DText(font, VTEXT("Hello, World"), Vector2(20,20), 1.0f, Colors::White);
  }
}

void TestGame::VOnShutdown()
{

}


int main(int argc, char* argv[])
{
  DebugPrintF(os_exec_dir().c_str());
  TestGame game;

  return game.Run();
}
