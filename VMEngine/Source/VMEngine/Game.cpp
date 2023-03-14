#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"
#include "VMEngine/Graphics/Mesh.h"
#include "VMEngine/Input.h"

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
		// create an input to detect the input
		GameInput = new  Input();
		// create a shader
		ShaderPtr TextureShader = Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});

		// create textures
		TexturePtr TConcrete = Graphics->CreateTexture("Game/Textures/ConcreteFloor.jpg");
		TexturePtr TGrid = Graphics->CreateTexture("Game/Textures/ColourGrid.jpg");

		//create a Mesh
		Poly = Graphics->CreateSimpleMeshShape(GeomatricShapes::Cube, TextureShader, { TConcrete });
		Poly2 = Graphics->CreateSimpleMeshShape(GeomatricShapes::Cube, TextureShader, { TGrid });

		//initial transformations for the meshes
		Poly->Transform.Location.x = 1.0f;
		Poly2->Transform.Location.x = -1.0f;
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
	// run the inout detection for the game input
	GameInput->ProcessInput();
	
}

void Game::update()
{
	// set delta time first always 
	static double LastFrameTime = 0.0;
	// set current time since the game has passed
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	// find the time fidderence between the last and current frame
	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	// set delta time as seconds
	DeltaTime = NewDeltaTime / 1000.0;
	//update the last frametie for the next update
	LastFrameTime = CurrentFrameTime;

	//TODO: handle logic
	Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();
	Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();
	Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();

	Poly2->Transform.Rotation.z += 50.0f * GetFDeltaTime();
	Poly2->Transform.Rotation.z += 50.0f * GetFDeltaTime();
	Poly2->Transform.Rotation.z += 50.0f * GetFDeltaTime();


	Vector3 CameraInput = Vector3(0.0f);

	// move cam forward
	if (GameInput->IsKeyDown(SDL_SCANCODE_W))
	{
		CameraInput.z = 1.0f;
	}

	// move cam backward
	if (GameInput->IsKeyDown(SDL_SCANCODE_S))
	{
		CameraInput.z = -1.0f;
	}

	// move cam left
	if (GameInput->IsKeyDown(SDL_SCANCODE_A))
	{
		CameraInput.x = 1.0f;
	}

	// mve cam right
	if (GameInput->IsKeyDown(SDL_SCANCODE_D))
	{
		CameraInput.x = -1.0f;
	}

	// move cam up
	if (GameInput->IsKeyDown(SDL_SCANCODE_Q))
	{
		CameraInput.y = -1.0f;
	}

	// move cam down
	if (GameInput->IsKeyDown(SDL_SCANCODE_E))
	{
		CameraInput.y = 1.0f;
	}

	CameraInput *= 3.0f * GetFDeltaTime();

	Graphics->EngineDefaultCam += CameraInput;

}

void Game::Draw()
{
	//TODO: draw graphis to screen
	Graphics->Draw();
}

void Game::CloseGame()
{
	////TODO: cleanup code
	delete GameInput;
}
