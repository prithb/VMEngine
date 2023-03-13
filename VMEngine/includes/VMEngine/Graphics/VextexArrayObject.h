#pragma once
#include"VMEngine/CoreMinimal.h"

const PositionMatrix TrianglePositions
{
	// x	//y		//z		//colour			//text coords
	-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// botton left
	0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// bottom right
	0.0f,	 0.5f,	 0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 1.0f	// top 

};

const IndicesMatrix TriangleIndices
{
	0, 1, 2
};

const PositionMatrix PolyPositions
{
	// x	//y		//z		//colour			// text coords
	-0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// botton left
	0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// bottom right
	0.5f,	 0.5f,	 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		 // top right
	-0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f	// top left

};

const IndicesMatrix PolyIndices
{
	0, 3, 1,		// triangle 1
	3, 2, 1,		// triangle 2
};

const PositionMatrix CirclePositions
{
	// x	//y		//z		// colour				//text coord
	0.0f,	0.575f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,
	0.3f,	0.5f,	0.0f,	0.0f,	1.0f,	0.5f,	0.0f,	0.0f,
	0.5f,	0.3f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,
	0.575f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,
	0.5f,	-0.3f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,
	0.3f,	-0.5f,	0.0f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,
	0.0f,	-0.575f,0.0f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,
	-0.3f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.5f,	0.0f,	0.0f,
	-0.5f,	-0.3f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
	-0.575f,-0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
	-0.5f,	0.3f,	0.0f,	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,
	-0.3f,	0.5f,	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	0.0f,
	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f
};
const IndicesMatrix CircleIndices
{
	0, 1, 12,
	1, 2, 12,
	2, 3, 12,
	3, 4, 12,
	4, 5, 12,
	5, 6, 12,
	6, 7, 12,
	7, 8, 12,
	8, 9, 12,
	9, 10, 12,
	10, 11, 12,
	11, 0, 12
};

class VertexArrayObject
{
public:
	VertexArrayObject(GeomatricShapes ChosenShape);
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