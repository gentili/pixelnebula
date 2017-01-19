#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader(const char *, const char *, const int);
private:
	GLuint _id;
	GLuint convertShaderType2GLuint(const int shaderType);
};

class ShaderManager
{
private:
	
public:
	static bool Init();
};