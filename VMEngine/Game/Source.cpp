#include "VMEngine/Game.h"

int main(int argc, char** argv)
{
	Game::GetGameInsatnce().start("VMEngine | An OpenGL Engine", false, 720, 720);

	Game::DestroyGameInstance();

	return 0;
}