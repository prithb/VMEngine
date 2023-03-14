#include "VMEngine/Graphics/Mesh.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "VMEngine/Graphics/Texture.h"
#include "VMEngine/Graphics/VextexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"

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

	// initialise the static variabe to check if any change to transform
	static CTransform OldTransform;

	if (Transform != OldTransform)
	{
		OldTransform = Transform;

		glm::mat4 MatTransform = glm::mat4(1.0f);

		// translate - rotate - scale ---- in this order
		// translate
		MatTransform = glm::translate(MatTransform, Transform.Location);
		// rotate
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.z), Vector3(0.0f, 0.0f, 1.0f));
		//scale
		MatTransform = glm::scale(MatTransform, Transform.Scale);

		// update the shader with the new transform
		MeshShader->SetMat4("model", MatTransform);

	}

	Game::GetGameInsatnce().GetGraphicsEngine()->ApplyScreenTransformations(MeshShader);

	//draw the vao
	MeshVAO->Draw();
}
