#pragma once

#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <fstream>

class Shader
{
public:
	explicit Shader(const char* vertShaderPath, const char* fragShaderPath);
	~Shader();

	void Use();

	void setBool(const char* name, bool value);
	void setInt(const char* name, int value);
	void setfloat(const char* name, float value);
	unsigned int ID;
};