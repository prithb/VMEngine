#include "VMEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "VMEngine/Graphics/VextexArrayObject.h"
#include"VMEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


GraphicsEngine::GraphicsEngine()
{
	sdlWindow = nullptr;
	sdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	// this will handle deleting the SDL window from the memory
	SDL_DestroyWindow(sdlWindow);
	// destroy the GL context from SDL
	SDL_GL_DeleteContext(sdlGLContext);
	// close the SDL framework
	SDL_Quit();

	cout << "destroy graphics engine..." << endl;
}


bool GraphicsEngine::InitGE(const char* Wtitle, bool bFullscreen, int WWidth, int WHeight)
{
	// maek sure SDL initialises
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Failed:" << SDL_GetError() << endl;
		return false;
	}

	// use openGL 4.6 compatability and set default attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);

	// set the ful screen flag
	int FullscreenFlag = 0;

	if (bFullscreen)
	{
		FullscreenFlag - SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}

	else
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	// create the SDL2 window
	sdlWindow = SDL_CreateWindow(
		Wtitle, // title of the window 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // location of widow 
		WWidth, WHeight, // width of the window 
		FullscreenFlag
	);

	// if the window fails the erroe log
	if (sdlWindow == nullptr)
	{
		cout << "SDL window Failed:" << SDL_GetError() << endl;
		return false;
	}

	// add all the gl attributes to the window 
	sdlGLContext = SDL_GL_CreateContext(sdlWindow) ;

	if (sdlGLContext == NULL)
	{
		cout <<"SDL GL Context Failed:" << SDL_GetError() << endl;
		return false;
	}

	// to make glew wor we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK)
	{
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	// present the new graphics using opengl
	SDL_GL_SwapWindow(sdlWindow);
}

void GraphicsEngine::CLearGraphics()
{
	// set the backf=ground colour
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	CLearGraphics();

	HandleWireframeMode(false);

	vmuint index = 0;
	// todo: add anything that render between these two function
	for (VAOPtr VAO : VAOs)
	{
		Shader->RunShader();

		// move the object
		glm::mat4 transform = glm::mat4(1.0f);

		if (index == 0) // square
		{
			// move int the x, y or z direction based on the amount added
			transform = glm::translate(transform, glm::vec3(0.5f, 0.0, 0.0f));
			// radians is rotation amount
			//vec3 is the direction to rotate in
			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));
		}
		else if (index == 1) // triangle
		{
			transform = glm::translate(transform, glm::vec3(-0.5f, 0.0, 0.0f));
			// x and y will work for out 2D shaped
			// z must be larget than 0 or you wont see the object (1 is default)
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));
		}

		Shader->SetMat4("transform", transform);

		// draw each VAO
		VAO->Draw();

		index++;
	}

	index = 0;

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return sdlWindow;
}

void GraphicsEngine::CreateVAO(GeomatrixShapes Shape)
{
	// create a new VAO as a shared pointer
	VAOPtr NewVAO = make_shared<VAO>(Shape);
	//add it to the stack
	VAOs.push_back(NewVAO);
}

void GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	// create a new hader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	// initialise the shader into opengl using the file path
	NewShader->InitVFShader(ShaderFilePaths);

	// add the shader to our graphics engine
	Shader = NewShader;


}

void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	// if we wireframe mode is set, change it, vice cersa
	if (bShowWireframeMode != bWireframeMode);
	{
		bWireframeMode = bShowWireframeMode;
		
		// change how openGL REnders between the vertices
		if (bWireframeMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		}
		cout << "wireframe mode updated..." << endl;
	}
}
