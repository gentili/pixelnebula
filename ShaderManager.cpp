#include <string>
#include <iostream>
#include <vector>

#include "ShaderManager.h"
#include "Shaders.h"

using namespace std;

Shader::Shader(const char * name, const char * text, const int type)
{
	_name = name;
	_id = glCreateShader(convertShaderType2GLuint(type));
	if (_id <= 0)
		throw new runtime_error("Invalid ID when trying to create shader");
	glShaderSource(_id, 1, &text, NULL);
	glCompileShader(_id);
	GLint isCompiled;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint length;
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> errLog(length);
		glGetShaderInfoLog(_id, length, &length, &errLog[0]);
		string errStr("Shader failed to compile: ");
		errStr.append(name);
		errStr += "\n";
		errStr.append(errLog.begin(), errLog.end());
		throw runtime_error(errStr);
	}
	cout << name << ":" << _id << endl;
}

GLuint Shader::convertShaderType2GLuint(const int shaderType) {
	switch (shaderType) {
	case(FRAGMENT):
		return GL_FRAGMENT_SHADER;
	case(VERTEX):
		return GL_VERTEX_SHADER;
	default:
		string errStr("Invalid ShaderType ");
		errStr += shaderType;
		errStr += " for Shader ";
		errStr += _name;
		throw runtime_error(errStr);
	}
}

bool ShaderManager::Init()
{
	for (int i = 0; i < shaderCount; i++) {
		auto shader = new Shader(shaderNames[i], shaderText[i], shaderType[i]);
	}
	return true;
}