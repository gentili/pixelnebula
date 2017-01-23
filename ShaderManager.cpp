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
	cout << "Shader::Shader(" << _name << ":" << _id << ")" << endl;
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
}

GLuint Shader::convertShaderType2GLuint(const int shaderType) 
{
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

ShaderProgram::ShaderProgram(const char * name)
{
	_name = name;
	_id = glCreateProgram();
	cout << "ShaderProgram::ShaderProgram(" << _name << ":" << _id << ")" << endl;
}

void ShaderProgram::add(unique_ptr<Shader> shader) {
	_shaders.insert(make_pair(shader->getName(), std::move(shader)));
}

void ShaderProgram::attachAndLink()
{
	
	cout << "ShaderProgram::AttachAndLink(" << _name << ")" << endl;
	for (auto itr = _shaders.begin();
		itr != _shaders.end(); 
		itr++) {
		glAttachShader(_id, itr->second->getId());
	}
	glLinkProgram(_id);
	GLint isLinked;
	glGetProgramiv(_id, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> errLog(length);
		glGetShaderInfoLog(_id, length, &length, &errLog[0]);
		string errStr("Shader Program failed to link: ");
		errStr.append(_name);
		errStr += "\n";
		errStr.append(errLog.begin(), errLog.end());
		throw runtime_error(errStr);
	}
	GLint attr_count;
	glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES,&attr_count);
	cout << "Active attributs:" << attr_count << endl;
	for (int i = 0; i < attr_count; i++) {
		std::vector<GLchar> attrName(20);
		glGetActiveAttrib(_id, i, (GLsizei) attrName.size(), NULL, NULL, NULL, &attrName[0]);
		cout << "    " << attrName.data() << endl;
	}
	GLint uni_count;
	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &uni_count);
	cout << "Active uniforms:" << uni_count << endl;
	for (int i = 0; i < uni_count; i++) {
		std::vector<GLchar> uniName(20);
		glGetActiveUniform(_id, i, (GLsizei) uniName.size(), NULL, NULL, NULL, &uniName[0]);
		cout << "    " << uniName.data() << endl;
	}
}

GLuint ShaderProgram::getAttributeLocation(string name)
{
	auto loc = glGetAttribLocation(_id, name.c_str());
	if (loc < 0) {
		string errstr("No attribute ");
		errstr += name;
		errstr += " found in shader program ";
		errstr += _name;
		throw runtime_error(errstr);
	}
	return loc;
}

GLuint ShaderProgram::getUniformLocation(string name)
{
	auto loc = glGetUniformLocation(_id, name.c_str());
	if (loc < 0) {
		string errstr("No uniform ");
		errstr += name;
		errstr += " found in shader program ";
		errstr += _name;
		throw runtime_error(errstr);
	}
	return loc;
}

void ShaderProgram3D::attachAndLink()
{
	ShaderProgram::attachAndLink();
	_uniformIndex_modelMatrix = getUniformLocation("modelMatrix");
	_uniformIndex_viewMatrix = getUniformLocation("viewMatrix");
	_uniformIndex_projectionMatrix = getUniformLocation("projectionMatrix");
}

std::map<std::string, std::unique_ptr<ShaderProgram>> ShaderManager::_shaderPrograms;

bool ShaderManager::Init()
{
	for (int i = 0; i < shaderCount; i++) {
		if (_shaderPrograms.count(shaderProgramNames[i]) == 0) {
			ShaderProgram * shaderProgram = shaderProgramType[i] == THREE_D ?
				new ShaderProgram3D(shaderProgramNames[i]) :
				new ShaderProgram(shaderProgramNames[i]);
			_shaderPrograms.insert(std::make_pair(shaderProgramNames[i], 
				std::unique_ptr<ShaderProgram>(shaderProgram)));
		}
		auto shaderProgramItr = _shaderPrograms.find(shaderProgramNames[i]);
		shaderProgramItr->second->add(std::unique_ptr<Shader>(new Shader(shaderNames[i], shaderText[i], shaderType[i])));
	}

	for (auto itr = _shaderPrograms.begin();
		itr != _shaderPrograms.end();
		itr++) {
		itr->second->attachAndLink();

	}

	return true;
}