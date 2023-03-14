#include "VMEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "VMEngine/Graphics/Mesh.h"
#include"VMEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VMEngine/Graphics/Texture.h"


GraphicsEngine::GraphicsEngine()
{
	sdlWindow = nullptr;
	sdlGLContext = NULL;
	bWireframeMode = false;
	EngineDefaultCam = Vector3(0.0f, 0.0f, -2.0f);
}

GraphicsEngine::~GraphicsEngine()
{
	// clear the mesh stack
	MeshStack.clear();

	//clear the shader
	 Shader = nullptr;
	
	// remove texture from memory
	TextureStack.clear();

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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);

	// set the ful screen flag
	int FullscreenFlag = 0;

	if (bFullscreen)
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
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

	// enable 3D depth
	glEnable(GL_DEPTH_TEST);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	CLearGraphics();

	HandleWireframeMode(false);

	// run through each mesh and call its draw method
	for (MeshPtr LMesh : MeshStack)
	{
		LMesh->Draw();
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return sdlWindow;
}

MeshPtr GraphicsEngine::CreateSimpleMeshShape(GeomatricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	// initialise a new mesh class
	MeshPtr NewMesh = make_shared<Mesh>();

	// make sure it worked
	if (!NewMesh->CreateSimpleShape(Shape, MeshShader, MeshTextures))
		return nullptr;

	// add mesh into the stack of mesh to be rendered
	MeshStack.push_back(NewMesh);

	// return the new mesh
	return NewMesh;
}

ShaderPtr GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	// create a new hader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	// initialise the shader into opengl using the file path
	NewShader->InitVFShader(ShaderFilePaths);

	// add the shader to our graphics engine
	Shader = NewShader;

	return NewShader;
}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;

	// run through al the textures and check if one with the same path exists
	for (TexturePtr TestTexture : TextureStack)
	{
		// if we fin texture with the same file path
		if (TestTexture->GetFilePath() == FilePath)
		{
			// pass in the already reated texture
			NewTexture = TestTexture;
			cout << "Texture found! assigning current texture." << endl;
			break;
		}

	}

	// if there is no texture aready in existance
	if (NewTexture == nullptr)
	{
		cout << "create a new texture ..." << endl;

		// create a new teture as a shared_ptr
		NewTexture = make_shared<Texture>();

		// if the filer was found assign it to the texture stack
		if (NewTexture->CreateTextureFromFilePath(FilePath))
		{
			cout << "Texture" 
			<< NewTexture->GetID()
				<< "creation success!addig to the texture stack" 
				<< endl;

			// add the texture to the texture stack
			TextureStack.push_back(NewTexture);
		}
	}

	return NewTexture;
}

void GraphicsEngine::ApplyScreenTransformations(ShaderPtr Shader)
{
	// the angle of the camera planes - basically your zoom
	float FOV = 70.0f;
	// view position of the camera / view space
	Vector3 ViewPosition = EngineDefaultCam;
	// find the size of the screen and calculate the aspect ratio
	int WWidth, WHeight = 0;
	// use the sdl to get the size of the window 
	SDL_GetWindowSize(sdlWindow , &WWidth, &WHeight);
	// calculate the aspect ratio from the window size
	float AR = static_cast<float> (WWidth) / static_cast<float>(max(WHeight, 1));

	// create the default coordinates for the projection and view
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//update the coordinates for 3D
	view = glm::translate(view, ViewPosition);
	// create the prospective view to allow us to see in 3D
	// also adjusting the near and far clip
	projection = glm::perspective(glm::radians(FOV), AR, 0.01f, 1000.0f);

	Shader->SetMat4("view", view);
	Shader->SetMat4("projection", projection);
}

void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	// if we wireframe mode is set, change it, vice cersa
	if (bShowWireframeMode != bWireframeMode)
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
