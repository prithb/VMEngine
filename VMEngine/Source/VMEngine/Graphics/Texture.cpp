#include "VMEngine/Graphics/Texture.h"
#include "GL/glew.h"
#include "stb_Image/stb_image.h"
#include <string>

Texture::Texture()
{
	TextureID = 0;
	FilePath = "";

	//assign a openGl tecture ID
	glGenTextures(1, &TextureID);
	// set the current texture as the current opengl Texture
	BindTexture();

	// set default geometry texture setting
	// set what happens if the teture doesnt fit the whole geometry
	// s = u = x --- t = v= y --- r = z (we dont use z for 2D texture)
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set how the image will blur between pixels as it scale uo and down resolution
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	cout << "Initialised Texture with ID: " << TextureID << endl;
}

Texture::~Texture()
{
	// destroy the texture from memory
	glDeleteTextures(1, &TextureID);

	cout << "texture " << TextureID << "delete " << endl;
}

bool Texture::CreateTextureFromFilePath(const char* FilePath)
{
	BindTexture();

	this->FilePath = FilePath;

	// hold the imported image data
	ImportImageData ImageData;

	// tell stbi to load our images in flipped
	stbi_set_flip_vertically_on_load(true);

	// loading the image using the file path and getting emage data
	unsigned char* RawImage = stbi_load(
		FilePath,
		&ImageData.w, &ImageData.h,
		&ImageData.channels,
		STBI_rgb_alpha
	);

	if (!RawImage)
	{
		cout << "Texture | Image couldn't be loaded " << endl;
		return false;
	}

	// create/ convert the image data into a openGL texture
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		ImageData.w, ImageData.h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		RawImage
	);

	// generate smaller versions of texture for when further away
	glGenerateMipmap(GL_TEXTURE_2D);

	// destroy the raw image data from memory
	stbi_image_free(RawImage);

	return true;
}

void Texture::BindTexture()
{
	//check that an id has been assigned then bid the teture as the current
	if (TextureID !=0)
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);
	}
	
}

void Texture::ActivateTexture(vmuint Index)
{
	if (TextureID != 0)
	{
		glActiveTexture(GL_TEXTURE0 + Index);
	}
	
}

void Texture::ResetTexture()
{
	// assigne the first texture to anything without a texture
	glActiveTexture(GL_TEXTURE0);
}
