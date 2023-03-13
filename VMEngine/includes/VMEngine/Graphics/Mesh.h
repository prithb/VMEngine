#pragma once
#include "VMEngine/CoreMinimal.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	// create the mesh out of VAo, a shader and textures
	bool CreateSimpleShape(GeomatricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures);

	// handle the drawing of all the required classes
	void Draw();

private:
	//store the shader this mesh requires
	ShaderPtr MeshShader;
	// store the textures this mesh requires
	TexturePtrStack MeshTextures;
	// create a new VAO for the mesh
	VAOPtr MeshVAO;
};