#pragma once
#include "VMEngine/CoreMinimal.h"

// hold the image data for conversion to the texture file
struct ImportImageData
{
	int w = 0;
	int h = 0;
	int channels = 0;
};

class Texture
{
public:
	Texture();
	~Texture();

	// create texture file from imported image path
	bool CreateTextureFromFilePath(const char* FilePath);

	// return the openGL texture ID
	vmuint GetID() const { return TextureID; }

	// bind the texture as the current texture in open gl
	void BindTexture();

	// assigns the televant data to the current loat texture
	void ActivateTexture(vmuint Index);

	// clear the texture in open gl
	static void ResetTexture();

	// return the file path
	const char* GetFilePath() const { return FilePath; }

private:
	// hold the ID for the texture in openGL
	vmuint TextureID;
	// hold the Filepath to avoid dupliates
	const char* FilePath;



};