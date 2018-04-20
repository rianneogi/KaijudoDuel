#include "ShaderProgram.h"
// #include <conio.h>

unsigned int gActiveShader = 0;

ShaderProgram::ShaderProgram()
{
	mProgramID = NULL;

	mUniformCount = 0;
	mMaxUniforms = 3;
	mUniformLocations = new GLint[mMaxUniforms];
}

ShaderProgram::ShaderProgram(int uniforms)
{
	mProgramID = NULL;

	mUniformCount = 0;
	mMaxUniforms = uniforms;
	mUniformLocations = new GLint[mMaxUniforms];
}

ShaderProgram::~ShaderProgram()
{
	//Free program if it exists
	freeProgram();
}

void ShaderProgram::freeProgram()
{
	//Delete program
	glDeleteProgram(mProgramID);
}

bool ShaderProgram::bind()
{
	debugOpengl("binding shader 0");

	//Use shader
	glUseProgram(mProgramID);

	return debugOpengl("binding shader");
}

void ShaderProgram::unbind()
{
	//Use default program
	glUseProgram(NULL);
}

GLuint ShaderProgram::getProgramID()
{
	return mProgramID;
}

void ShaderProgram::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
			// _getch();
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
		// _getch();
	}
}

void ShaderProgram::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
			// _getch();
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
		// _getch();
	}
}

GLuint ShaderProgram::loadShaderFromFile(std::string path, GLenum shaderType)
{
	//Open file
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	//Source file loaded
	if (sourceFile)
	{
		//Get shader source
		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());

		//Create shader ID
		shaderID = glCreateShader(shaderType);

		//Set shader source
		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

		//Compile shader source
		glCompileShader(shaderID);

		//Check shader for errors
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
			printShaderLog(shaderID);
			glDeleteShader(shaderID);
			shaderID = 0;
			// _getch();
		}
	}
	else
	{
		printf("Unable to open file %s\n", path.c_str());
		// _getch();
	}

	return shaderID;
}

bool ShaderProgram::loadProgram(std::string path)
{
	//Generate program
	mProgramID = glCreateProgram();

	//Load vertex shader
	GLuint vertexShader = loadShaderFromFile(path+".glvs", GL_VERTEX_SHADER);

	//Check for errors
	if (vertexShader == 0)
	{
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach vertex shader to program
	glAttachShader(mProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = loadShaderFromFile(path+".glfs", GL_FRAGMENT_SHADER);

	//Check for errors
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Attach fragment shader to program
	glAttachShader(mProgramID, fragmentShader);

	//Link program
	glLinkProgram(mProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", mProgramID);
		printProgramLog(mProgramID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		return false;
	}

	//Clean up excess shader references
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

void ShaderProgram::setMaxUniforms(int uniforms)
{
	mMaxUniforms = uniforms;
	mUniformLocations = new int[mMaxUniforms];
	mUniformCount = 0;
}

void ShaderProgram::setUniformInt(int id, int val)
{
	//assert(id < mUniformCount);
	glUniform1i(mUniformLocations[id], val);
}

void ShaderProgram::setUniformMat4f(int id, glm::mat4 matrix)
{
	assert(id < mUniformCount);
	glUniformMatrix4fv(mUniformLocations[id], 1, GL_FALSE, glm::value_ptr(matrix));
}
void ShaderProgram::setUniformVec3f(int id, glm::vec3 vec)
{
	assert(id < mUniformCount);
	glUniform3fv(mUniformLocations[id], 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniformVec4f(int id, glm::vec4 vec)
{
	assert(id < mUniformCount);
	glUniform4fv(mUniformLocations[id], 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniformVec4f(std::string name, glm::vec4 vec)
{
	glUniform4fv(glGetUniformLocation(mProgramID, name.c_str()), 1, glm::value_ptr(vec));
}

int ShaderProgram::addUniform(std::string name)
{
	assert(mUniformCount < mMaxUniforms);
	mUniformLocations[mUniformCount] = glGetUniformLocation(mProgramID, name.c_str());
	mUniformCount++;
	return mUniformCount - 1;
}
