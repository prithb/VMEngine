#pragma once
#include "VMEngine/CoreMinimal.h"



class Game
{
public: // Get the game instance or create one if it doesn't exist 
	static Game& GetGameInsatnce();

	// Destroy the game running the destructor
	static void DestroyGameInstance();

	// start the gane/app
	// load the window
	void start(const char* Wtitle, bool bFullscreen, int WWidth, int WHeight);


private:
	Game();
	~Game();

	// run the game loop
	void Run();

	
	// handle the I/O 
	void processInput();

	// handle game logic
	void update();


	// Handle the 3D graphics drawing to the screen
	//will clear and present each frame
	void Draw();

	// handle anything that need to be deleted when the game ends
	void CloseGame();

private:
	// boolean that ends the game
	bool bIsGameOver;

	// share pointer to the graphics of screen
	GraphicsEnginePtr Graphics;

	// temporary mesh variables
	MeshPtr Tri;
	MeshPtr Poly;


};