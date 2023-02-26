#pragma once
#include "SDL2/SDL.h"
#include"VMEngine/CoreMinimal.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	// create the window 
	bool InitGE(const char* Wtitle, bool bFullscreen, int WWidth, int WHeight);

	//show the ewest frame graphics
	void PresentGraphics();

	// claer the old frame graphics 
	void CLearGraphics();

	// handle rendering of our graphics

	void Draw();

	// return the sdl window 
	SDL_Window* GetWindow() const;

	//add a new VAO to the VAOStack using a shape define
	void CreateVAO(GeomatrixShapes Shape);

	// add new shader
	// @param 1 - vertex Shader
	// @param 2 - fragment shader
	void CreateShader(VFShaderParams ShaderFilePaths);

private:
	// this will hold the window 
	SDL_Window* sdlWindow;

	// this will allow openGL to work in sdl
	SDL_GLContext sdlGLContext;
	// stack all the VAOs
	VAOStack VAOs;
	// handle wireframe mode
	void HandleWireframeMode(bool bShowWireframeMode);
	// set wireframe
	bool bWireframeMode;

	// single shader
	ShaderPtr Shader;
};
