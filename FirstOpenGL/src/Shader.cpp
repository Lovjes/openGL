#include "Shader.h"
#include <string>

Shader::Shader(const char* vertShaderPath, const char* fragShaderPath)
{

	//Load shader file 
	std::string vertShaderCode;
	std::string fragShaderCode;
	std::ifstream vertShaderLoader;
	std::ifstream fragShaderLoader;
	vertShaderLoader.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragShaderLoader.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		vertShaderLoader.open(vertShaderPath);
		fragShaderLoader.open(fragShaderPath);

		std::stringstream vertShaderBuffer;
		std::stringstream fragShaderBuffer;

		vertShaderBuffer << vertShaderLoader.rdbuf();
		fragShaderBuffer << fragShaderLoader.rdbuf();

		vertShaderLoader.close();
		fragShaderLoader.close();

		vertShaderCode = vertShaderBuffer.str();
		fragShaderCode = fragShaderBuffer.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failed to load shader files!" << std::endl;
	}

	const char* vertShader_c = vertShaderCode.c_str();
	const char* fragShader_c = fragShaderCode.c_str();

	// check shader compilation 
	int success;
	char shaderLog[512];

	//vertex shader
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShader_c, NULL);
	glCompileShader(vertShader);

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, shaderLog);
		std::cout << "vertex shader compile failed: " << shaderLog << std::endl;
	}

	//fragment shader
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShader_c, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, shaderLog);
		std::cout << "fragment shader compile failde: " << shaderLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, shaderLog);
		std::cout << "shader link failed: " << shaderLog << std::endl;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	ID = shaderProgram;
		
}

Shader::~Shader()
{

}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::setBool(const char* name, bool value)
{
	int loc = glGetUniformLocation(ID, name);
	if (loc < 0)
	{
		std::cout << "can't find bool param named " << name << "!" << std::endl;
		return;
	}
	glUniform1i(loc, (int)value);
}

void Shader::setInt(const char* name, int value)
{
	int loc = glGetUniformLocation(ID, name);
	if (loc < 0)
	{
		std::cout << "can't find int param named " << name << "!" << std::endl;
		return;
	}
	glUniform1i(loc, value);
}

void Shader::setfloat(const char* name, float value)
{
	int loc = glGetUniformLocation(ID, name);
	if (loc < 0)
	{
		std::cout << "can't find int param named " << name << "!" << std::endl;
		return;
	}
	glUniform1f(loc, value);
}
