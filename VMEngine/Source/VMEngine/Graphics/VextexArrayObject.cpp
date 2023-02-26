#include "VMEngine/Graphics/VextexArrayObject.h"
#include "GL/glew.h"

VertexArrayObject::VertexArrayObject(GeomatrixShapes ChosenShape)
{
	ID = EAB = VAB = 0;

	// localised version of the chosen matrices
	PositionMatrix ChosenPosition = PositionMatrix();
	IndicesMatrix ChosenIndices = IndicesMatrix();

	// switch the chosen matrices depending on the selected geometry type
	switch (ChosenShape)
	{
	case GeomatrixShapes::Triangle:
		ChosenPosition = TrianglePositions;
		ChosenIndices = TriangleIndices;
		break;
	case GeomatrixShapes::Polygon :
		ChosenPosition = PolyPositions;
		ChosenIndices = PolyIndices;
		break;
	case GeomatrixShapes::Circle:
		ChosenPosition = CirclePositions;
		ChosenIndices = CircleIndices;
		break;
	default:
		break;
	}

	Shape.PositionMatrix = ChosenPosition;
	Shape.IndicesMatrix = ChosenIndices;

	// Handle the positions
	// create the ID for our VAO
	glGenVertexArrays(1, &ID);

	//bind the data to this vertex array
	glBindVertexArray(ID);

	// create an id for our array buffer
	glGenBuffers(1, &VAB);
	// bind the above IDs to openGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	// Run through the data ad attach the vertices to VAB
	glBufferData(GL_ARRAY_BUFFER,
		Shape.PositionMatrix.size() * sizeof(float),
		&Shape.PositionMatrix[0],
		GL_STATIC_DRAW);
	
	// handle the indices
	// create an id for our element array buffer
	glGenBuffers(1, &EAB);
	// bind the above ID to openGL as the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	// run throught the data and attach the indices to the EAB
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		Shape.IndicesMatrix.size() * sizeof(vmuint),
		&Shape.IndicesMatrix[0],
		GL_STATIC_DRAW);

	// assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,					// data set - 0= the first data set in the array
		3,					// how many numbers in our matrix t ake a traingle
		GL_FLOAT, GL_FALSE, // data type, whether you want to noralise the values
		sizeof(float) * 3,	// stride - the length it tales to get to each number
		(void*)0			// offset of how many number to skip in the matrix
	);

	// enable the vertex array
	glEnableVertexAttribArray(0);

	//assign the colour to the shader
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 6,
		(void*)( 3 * sizeof(float))
	);

	// enabe the colour array
	glEnableVertexAttribArray(0);

	// clear the buffer
	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	// cleanup the VAO in openGl
	glDeleteVertexArrays(1, &ID);

	//cleanp the vectors
	Shape.PositionMatrix.clear();
	Shape.IndicesMatrix.clear();

	cout << "Deleted VAO...." << endl;
}

void VertexArrayObject::Draw()
{
	// bind out VAO to the current buffer
	glBindVertexArray(ID);
	// draw the 3D object/ VAO
	glDrawElements(GL_TRIANGLES,	// what type of object are we drawing 
		Shape.IndicesMatrix.size(), // how many vertices we draw
		GL_UNSIGNED_INT,			// what is the type of data thats being input
		(void*)0);					// how many should we skip?
	// clear the VAO from current array to allow for the next object
	glBindVertexArray(0);
}
