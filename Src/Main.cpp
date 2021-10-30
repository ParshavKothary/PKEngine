#include <Core/PKEngine.h>
#include <PongGame.h>

using namespace pkengine;

int main()
{
    CPKEngine Engine;
    Engine.CreateGame<CPongGame>(800, 800, "TestGame");
    Engine.RunGame();

	return 0;
}