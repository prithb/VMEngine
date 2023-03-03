#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"

Game& Game::GetGameInsatnce()
{
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	static Game* GameInsatnce = &GetGameInsatnce();

	delete GameInsatnce;
}

void Game::start(const char* Wtitle, bool bFullscreen, int WWidth, int WHeight)
{
	Graphics = make_shared<GraphicsEngine>();

	if (!Graphics->InitGE(Wtitle, bFullscreen, WWidth, WHeight))
	{
		bIsGameOver = true;
	}

	Run();
}

Game::Game()
{
	cout << "Game Initialised" << endl;

	Graphics = nullptr;
	bIsGameOver = false;

}

Game::~Game()
{
	// since nothing else is storing graphics in memory
	// this will destroy the graphics from the memory
	Graphics = nullptr;

	cout << "Game Over ...." << endl;
}

void Game::Run()
{
	if (!bIsGameOver)
	{
		// create a shader
		Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});
		//create a VAOs
		Graphics->CreateVAO(GeomatrixShapes::Triangle);
		Graphics->CreateVAO(GeomatrixShapes::Polygon);
	}
	

	// as long as the game is not over run the loop
	while(!bIsGameOver)
	{
		//make sure we process waht the user has done
		processInput();

		// apply the logic base on the inputs and the game logic
		update();

		// render the screen based on the function above
		Draw();
	}
	//clean the game after it ends
	CloseGame();
}

void Game::processInput()
{
	//TODO: Handle input
	SDL_Event PollEvent;

	// this is waiting for inputs to be pressed
	while (SDL_PollEvent(&PollEvent))
	{
		// checking while the input is pressed
		switch (PollEvent.type)
		{
		case SDL_QUIT : // on close button pressed
			bIsGameOver = true;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	//TODO: handle logic
}

void Game::Draw()
{
	//TODO: draw graphis to screen
	Graphics->Draw();
}

void Game::CloseGame()
{
	////TODO: cleanup code
}
