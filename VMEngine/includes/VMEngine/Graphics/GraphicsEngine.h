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
	MeshPtr CreateSimpleMeshShape(GeomatricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures);

	// add new shader
	// @param 1 - vertex Shader
	// @param 2 - fragment shader
	ShaderPtr CreateShader(VFShaderParams ShaderFilePaths);

	//create texture and add it to the texture stack
	// avoid Duplicate
	TexturePtr CreateTexture(const char* FilePath);

private:
	// this will hold the window 
	SDL_Window* sdlWindow;

	// this will allow openGL to work in sdl
	SDL_GLContext sdlGLContext;
	// handle wireframe mode
	void HandleWireframeMode(bool bShowWireframeMode);
	// set wireframe
	bool bWireframeMode;

	// single shader
	ShaderPtr Shader;
	//store a vector of textures
	TexturePtrStack TextureStack;
	//store all meshes in the game
	MeshPtrStack MeshStack;
};
