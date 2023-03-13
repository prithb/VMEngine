#include "VMEngine/Graphics/Mesh.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "VMEngine/Graphics/Texture.h"
#include "VMEngine/Graphics/VextexArrayObject.h"

Mesh::Mesh()
{
	cout << "Mesh | initialised Mesh." << endl;
}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshTextures.clear();
	MeshVAO = nullptr;

	cout << "Mesh | Mesh Destroyed." << endl;
}

bool Mesh::CreateSimpleShape(GeomatricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	cout << "Mesh | creating Mesh. " << endl;

	// creating the VAO
	MeshVAO = make_shared<VAO>(Shape);

	// validate the mesh was created
	if (MeshVAO == nullptr)
	{
		cout << "Mesh Failed to be created. " << endl;
		return false;
	}

	//assign the shader and textures
	this->MeshShader = MeshShader;
	this->MeshTextures = MeshTextures;

	cout << "Mesh | Mesh Created successfully." << endl;

	return true;
}

void Mesh::Draw()
{
	//activate the shader that this mesh uses
	MeshShader->RunShader();

	// activate the required textures for this mesh
	for (vmuint Index = 0; Index < MeshTextures.size(); Index++)
	{
		// activating the texture through openGl
		MeshTextures[Index]->ActivateTexture(Index);
		//setting the texture number as the active texture in the shader
		MeshShader->SetInt("TextureColour", Index);
		// binding the texture to the shader
		MeshTextures[Index]->BindTexture();
	}

	//draw the vao
	MeshVAO->Draw();
}
