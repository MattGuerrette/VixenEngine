
#include <vix_game.h>

#include <vix_osutil.h>
#include <vix_stringutil.h>
#include <vix_debugutil.h>

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
	
};

TestGame::TestGame()
	: IGame()
{

}

void TestGame::VOnStartup()
{

}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{

}

void TestGame::VOnShutdown()
{

}

int main(int argc, char* argv[])
{
	TestGame test;

	return test.Run();
}