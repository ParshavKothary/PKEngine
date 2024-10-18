#include <Core/PKEngine.h>
#include <PongGame.h>

using namespace pkengine;

void RunGame()
{
    CPKEngine Engine;
    Engine.CreateGame<ponggame::CPongGame>(1200, 800, "TestGame");
    Engine.RunGame();
}

int main()
{
    RunGame();
	return 0;
}