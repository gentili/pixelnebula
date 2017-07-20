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
	cout << "\tActive attributes:" << attr_count << endl;
	for (int i = 0; i < attr_count; i++) {
		std::vector<GLchar> attrName(60);
		GLint size;
		GLenum type;
		glGetActiveAttrib(_id, i, (GLsizei) attrName.size(), NULL, &size, &type, &attrName[0]);
		cout << "\t\t" << attrName.data() << endl;
	}
	GLint uni_count;
	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &uni_count);
	cout << "\tActive uniforms:" << uni_count << endl;
	for (int i = 0; i < uni_count; i++) {
		std::vector<GLchar> uniName(60);
		GLint size;
		GLenum type;
		glGetActiveUniform(_id, i, (GLsizei) uniName.size(), NULL, &size, &type, &uniName[0]);
		cout << "\t\t" << uniName.data() << endl;
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

void ShaderProgram3D::setModelMatrix(mat4x4 modelMatrix)
{
	glUseProgram(_id);
	glUniformMatrix4fv(_uniformIndex_modelMatrix, 1, GL_FALSE, (const GLfloat *) modelMatrix);
}

void ShaderProgram3D::setViewMatrix(mat4x4 viewMatrix)
{
	glUseProgram(_id);
	glUniformMatrix4fv(_uniformIndex_viewMatrix, 1, GL_FALSE, (const GLfloat *) viewMatrix);
}

void ShaderProgram3D::setProjectionMatrix(mat4x4 projectionMatrix)
{
	glUseProgram(_id);
	glUniformMatrix4fv(_uniformIndex_projectionMatrix, 1, GL_FALSE, (const GLfloat *) projectionMatrix);
}

std::map<std::string, std::unique_ptr<ShaderProgram> > ShaderManager::_shaderPrograms;
std::map<std::string, ShaderProgram3D *> ShaderManager::_3DshaderPrograms;

bool ShaderManager::Init()
{
	for (int i = 0; i < shaderCount; i++) {
		if (_shaderPrograms.count(shaderProgramNames[i]) == 0) {
			ShaderProgram * shaderProgram;
			if (shaderProgramType[i] == THREE_D) {
				auto shaderProgram3D = new ShaderProgram3D(shaderProgramNames[i]);
				_3DshaderPrograms.insert(std::make_pair(shaderProgramNames[i],
					shaderProgram3D));
				shaderProgram = shaderProgram3D;
			}
			else {
				shaderProgram = new ShaderProgram(shaderProgramNames[i]);
			}
			_shaderPrograms.insert(std::make_pair(shaderProgramNames[i], 
				std::unique_ptr<ShaderProgram>(shaderProgram)));
		}
		auto shaderProgramItr = _shaderPrograms.find(shaderProgramNames[i]);
		shaderProgramItr->second->add(std::unique_ptr<Shader>(new Shader(shaderNames[i], shaderText[i], shaderType[i])));
	}

	for (auto itr = _shaderPrograms.begin();
		itr != _shaderPrograms.end();
		itr++)
		itr->second->attachAndLink();

	return true;
}

void ShaderManager::setShaderPrograms3DModelMatrix(mat4x4 modelMatrix)
{
	for (auto itr = _3DshaderPrograms.begin();
		itr != _3DshaderPrograms.end();
		itr++) {
		itr->second->setModelMatrix(modelMatrix);
	}
}

void ShaderManager::setShaderPrograms3DViewMatrix(mat4x4 viewMatrix)
{
	for (auto itr = _3DshaderPrograms.begin();
		itr != _3DshaderPrograms.end();
		itr++) {
		itr->second->setViewMatrix(viewMatrix);
	}
}

void ShaderManager::setShaderPrograms3DProjectionMatrix(mat4x4 projectionMatrix)
{
	for (auto itr = _3DshaderPrograms.begin();
		itr != _3DshaderPrograms.end();
		itr++) {
		itr->second->setProjectionMatrix(projectionMatrix);
	}
}

ShaderProgram * ShaderManager::getShaderProgram(string name) 
{
	auto itr = _shaderPrograms.find(name);
	if (itr == _shaderPrograms.end()) {
		string errstr("No such shader '");
		errstr += name;
                errstr += "'";
		throw runtime_error(errstr);
	}
	return itr->second.get();
}

ShaderProgram3D * ShaderManager::getShaderProgram3D(string name) 
{
	auto itr = _3DshaderPrograms.find(name);
	if (itr == _3DshaderPrograms.end()) {
		string errstr("No such shader '");
		errstr += name;
                errstr += "'";
		throw runtime_error(errstr);
	}
	return itr->second;
}
