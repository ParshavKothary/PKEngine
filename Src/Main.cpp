#include <Core/PKEngine.h>
#include <PongGame.h>

using namespace pkengine;

int main()
{
    CPKEngine Engine;
    Engine.CreateGame<ponggame::CPongGame>(1200, 800, "TestGame");
    Engine.RunGame();

	return 0;
}