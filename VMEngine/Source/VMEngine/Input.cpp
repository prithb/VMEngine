#include"VMEngine/Input.h"
#include "VMEngine/Game.h"
#include<iostream>

using namespace std;

Input::Input()
{
	// assign the current keys by default 
	KeyboardState = SDL_GetKeyboardState(NULL);
}

void Input::ProcessInput()
{
	//TODO: Handle input
	SDL_Event PollEvent;

	// this is waiting for inputs to be pressed
	while (SDL_PollEvent(&PollEvent))
	{
		// checking while the input is pressed
		switch (PollEvent.type)
		{
		case SDL_KEYDOWN:
			// update all the key on the keyboard with up or down states
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT: // on close button pressed
			Game::GetGameInsatnce().ClosingApp();
			break;
		default:
			break;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	// make sure the keyboard state is set
	if (KeyboardState == nullptr)
	{
		cout << "no keyboard state detected " << endl;
		return false;
	}

	// return the result of the key
	return static_cast<bool>(KeyboardState[key]);
}
