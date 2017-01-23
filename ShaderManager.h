#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <memory>

class Shader
{
public:
	Shader(const char *, const char *, const int);

	GLuint getId() { return _id; }
	std::string & getName() { return _name; }

private:
	GLuint _id;
	std::string _name;

	GLuint convertShaderType2GLuint(const int shaderType);
};

class ShaderProgram
{
public:
	ShaderProgram(const char *);

	GLuint getId() { return _id; }
	void add(std::unique_ptr<Shader>);
	void attachAndLink();
	GLuint getAttributeLocation(std::string);
	GLuint getUniformLocation(std::string);

private:
	GLuint _id;
	std::string _name;

	std::map<std::string, std::unique_ptr<Shader>> _shaders;
};

class ShaderManager
{
public:
	ShaderManager() = delete;
	static bool Init();

private:
	static std::map<std::string, std::unique_ptr<ShaderProgram>> _shaderPrograms;
};