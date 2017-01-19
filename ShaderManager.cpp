#include <iostream>

#include "ShaderManager.h"
#include "Shaders.h"

using namespace std;

Shader::Shader(const char * name, const char * text, const int type)
{
	_id = glCreateShader(convertShaderType2GLuint(type));
	cout << name << ":" << _id << endl;
}

GLuint Shader::convertShaderType2GLuint(const int shaderType) {
	switch (shaderType) {
	case(FRAGMENT):
		return GL_FRAGMENT_SHADER;
	case(VERTEX):
		return GL_VERTEX_SHADER;
	default:
		throw new exception("Invalid Shader Type");
	}
}

bool ShaderManager::Init()
{
	for (int i = 0; i < shaderCount; i++) {
		auto shader = new Shader(shaderNames[i], shaderText[i], shaderType[i]);
	}
	return true;
}