#include "VMEngine/Graphics/ShaderProgram.h"
#include "GL/glew.h"
#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram()
{
	ProgramID = 0;
}

ShaderProgram::~ShaderProgram()
{
	for (vmuint VFShaderID : VFShaderIDs)
	{
		// remove the shader from the program
		glDetachShader(ProgramID, VFShaderID);
		// delete the shader from memory
		glDeleteShader(VFShaderID);

	}
	// this will delete the shader program frm opengl
	glDeleteProgram(ProgramID);

	cout << " Shader Program" << ProgramID << " has been destroyed...." << endl;
}

bool ShaderProgram::InitVFShader(VFShaderParams ShaderFilePaths)
{
	ProgramID = glCreateProgram();

	if (ProgramID < 1)
	{
		cout << "shader program | can't assign program ID" << endl;
		return false;
	}

	bool VShader = AttachShader(ShaderFilePaths.VertexShaderPath, ShaderTypes::Vertex);
	bool FShader = AttachShader(ShaderFilePaths.FragmentShaderPath, ShaderTypes::Fragment);

	if (!VShader || !FShader)
	{
		return false;
	}

	// fail the whole function if link() fails
	return Link();
}

void ShaderProgram::RunShader()
{
	glUseProgram(ProgramID);
}

void ShaderProgram::SetMat4(const char* ShaderVariable, glm::mat4 Value)
{
	// finding the uniform mat4 called shadervariable and overwriting the value
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, ShaderVariable), 1, GL_FALSE, value_ptr(Value));
}

bool ShaderProgram::AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type)
{
	// store the shader code
	string ShaderCode;
	// store the file path in a file stream
	ifstream FilePathStream(ShaderFilePath);

	// check if the stream found the file
	if (!FilePathStream.is_open())
	{
		wclog << "Shader Program | " << ShaderFilePath << " not found." << endl;
		return false;
	}

	// temporary hold the shader for conversion in an string stream
	stringstream RawShaderCode;
	// convet the file to a single string
	RawShaderCode << FilePathStream.rdbuf();
	// convert it into a readable string
	ShaderCode = RawShaderCode.str();
	// close the string to the file
	FilePathStream.close();

	// initialise the shader ID variable for this specific shader
	vmuint ShaderID = 0;


	// change what happen with the ID depending on the type shader
	switch (Type)
	{
	case ShaderTypes::Vertex:
		ShaderID = glCreateShader(GL_VERTEX_SHADER);
		VFShaderIDs[0] = ShaderID;
		break;
	case ShaderTypes::Fragment:
		ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		VFShaderIDs[1] = ShaderID;
		break;
	default:
		break;
	}

	// put ur string code into the char arrray
	const char* ShaderCodePtr = ShaderCode.c_str();
	// add the shader code to the shader that we create above
	glShaderSource(ShaderID, 1, &ShaderCodePtr, NULL);
	// compile the shader
	glCompileShader(ShaderID);

	// initialise a variable that wil tel us if the shader has any logs
	int LogLength = 0;

	// check if there any og and add them to the loglength
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &LogLength);
	// print the log if there were any
	if (LogLength > 0)
	{
		// store the message 
		vector<char> LogMessage(LogLength + 1);
		// add the character into the vector array
		glGetShaderInfoLog(ShaderID, LogLength, NULL, &LogMessage[0]);

		// check if the compile failed
		int CompileStatus = GL_TRUE;
		// get the compile status - return a GL_TRUE if successful or GL_FALSE
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &CompileStatus);

		if (CompileStatus == GL_TRUE)
		{
			wclog << "Shader progam | compiler | " << ShaderFilePath <<
				" compile successfully with the following log:" << endl
				<< &LogMessage[0] << endl;
		}
		else
		{
			wclog << "Shader progam | compiler | " << ShaderFilePath <<
				" failed to compile with the following log:" << endl
				<< &LogMessage[0] << endl;
			return false;
		}
	}
	else
	{
		wclog << "Shader Program | " << ShaderFilePath << "Compile Successfully with no logs " << endl;
	}

	// attach te shader to the program id
	glAttachShader(ProgramID, ShaderID);

	

	return true;
}

bool ShaderProgram::Link()
{
	// add the program tp openGL
	glLinkProgram(ProgramID);

	// check the lonk for Logs ad errors
	int LogLength = 0;
	glGetShaderiv(ProgramID, GL_INFO_LOG_LENGTH, &LogLength);

	if (LogLength > 0)
	{
		vector<char> LogMessage(LogLength + 1);
		glGetShaderInfoLog(ProgramID, LogLength, NULL, &LogMessage[0]);

		int CompileStatus = GL_TRUE;
		glGetShaderiv(ProgramID, GL_COMPILE_STATUS, &CompileStatus);

		if (CompileStatus == GL_TRUE)
		{
			wclog << " Shader Program | Successfully linked with the following log:" << endl
				<< &LogMessage[0] << endl;
		}

		else
		{
			wclog << " Shader Program | failed to linked with the following log:" << endl
				<< &LogMessage[0] << endl;
			return false;
		}
	}
	else
	{
		wclog << " Shader Program | Successfully linked with no log:"<< endl;
	
	}

	return true;
}
