#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int vmuint;

// class/ type definatios
class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO>VAOPtr;
typedef vector<VAOPtr> VAOStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

// useful for shape data and VAOs Matrices
typedef vector<float> PositionMatrix;
typedef vector<vmuint> IndicesMatrix;

// this structure handle matrices for VADs
struct ShapeData
{
	vector<float> PositionMatrix;
	vector<vmuint> IndicesMatrix;
};

// a list of the geomatrix shapes available in VAO
enum class GeomatrixShapes
{
	Triangle = 0,
	Polygon,
	Circle
};

// store the parameter required to create shader program
struct VFShaderParams
{
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

// type of shader that can be accepted in oue shader program
enum class ShaderTypes
{
	Vertex = 0,
	Fragment
};
