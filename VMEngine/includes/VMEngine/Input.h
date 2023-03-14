#pragma once
#include "SDL2/SDL.h"

class Input
{
public:
	Input();

	// detect the input of the user
	void ProcessInput();

	// detect if a scpecific key is down base on sdl scancode
	// mint* SDL SCANCODE_KEY
	bool IsKeyDown(SDL_Scancode key);

private:
	const Uint8* KeyboardState;
};