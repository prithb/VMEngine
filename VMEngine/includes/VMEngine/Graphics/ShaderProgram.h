#pragma once
#include "VMEngine/CoreMinimal.h"
#include "glm/glm.hpp"
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	// this wil initialise our shader as a vertex fragment shader
	bool InitVFShader(VFShaderParams ShaderFilePaths);

	// run the shader program as the current shader to be interacted with the openGl
	void RunShader();

	// return the program id
	vmuint GetID() const { return ProgramID;  }

	//allow changing mat 4 variables in shader code
	void SetMat4(const char* ShaderVariable, glm::mat4 Value);
	// allow changing integer values in shader code
	void SetInt(const char* ShaderVarName, int Value);

private:
	// atttach the shader to the VAOs
	bool AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type);

	// link the shader to openGL
	bool Link();

private:
	// openGL will assgn an ID to our shader
	vmuint ProgramID;
	// array that will hold IDs to our unique shader
	// 0 - vertex
	//1 - fragment
	vmuint VFShaderIDs[2] = { 0 };
};
