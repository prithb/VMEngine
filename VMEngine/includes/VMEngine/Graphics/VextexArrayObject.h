#pragma once
#include"VMEngine/CoreMinimal.h"

const PositionMatrix TrianglePositions
{
	// x	//y		//z		//colour
	-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	// botton left
	0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	// bottom right
	0.0f,	 0.5f,	 0.0f,	0.0f, 0.0f, 1.0f	// top 

};

const IndicesMatrix TriangleIndices
{
	0, 1, 2
};

const PositionMatrix PolyPositions
{
	// x	//y		//z		//colour
	-0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,		// botton left
	0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,		// bottom right
	0.5f,	 0.5f,	 0.0f,	0.0f, 1.0f, 0.0f,		 // top right
	-0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.0f		// top left

};

const IndicesMatrix PolyIndices
{
	0, 3, 1,		// triangle 1
	3, 2, 1,		// triangle 2
};

const PositionMatrix CirclePositions
{
	// x	//y		//z
	0.0f,	0.575f,	0.0f,
	0.3f,	0.5f,	0.0f,
	0.5f,	0.3f,	0.0f,
	0.575f,	0.0f,	0.0f,
	0.5f,	-0.3f,	0.0f,
	0.3f,	-0.5f,	0.0f,
	0.0f,	-0.575f,0.0f,
	-0.3f,	-0.5f,	0.0f,
	-0.5f,	-0.34,	0.0f,
	-0.575f,-0.0f,	0.0f,
	-0.5f,	0.3f,	0.0f,
	-0.3f,	0.5f,	0.0f,
	0.0f,	0.0f,	0.0f
};
const IndicesMatrix CircleIndices
{
	
};

class VertexArrayObject
{
public:
	VertexArrayObject(GeomatrixShapes ChosenShape);
	~VertexArrayObject();

	void Draw();

private:
	ShapeData Shape;

	// this is our version of unsigned int
	//ID - ID for the VAO
	//VAB - ID for the vertices
	//EAB- ID for the Indices
	vmuint ID, VAB, EAB;
};