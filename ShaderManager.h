#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <memory>

#include <linmath.h>

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
	virtual void attachAndLink();
	GLuint getAttributeLocation(std::string);
	GLuint getUniformLocation(std::string);

protected:
	GLuint _id;
	std::string _name;

	std::map<std::string, std::unique_ptr<Shader> > _shaders;
};

class ShaderProgram3D : public ShaderProgram {
public:
	ShaderProgram3D(const char * name) : ShaderProgram(name) {};
	virtual void attachAndLink();
	void setModelMatrix(mat4x4);
	void setViewMatrix(mat4x4);
	void setProjectionMatrix(mat4x4);


protected:
	GLuint _uniformIndex_modelMatrix = 0;
	GLuint _uniformIndex_viewMatrix = 0;
	GLuint _uniformIndex_projectionMatrix = 0;
};

class ShaderManager
{
public:
	ShaderManager() = delete;
	static bool Init();
	static void setShaderPrograms3DModelMatrix(mat4x4);
	static void setShaderPrograms3DViewMatrix(mat4x4);
	static void setShaderPrograms3DProjectionMatrix(mat4x4);
	static ShaderProgram * getShaderProgram(std::string);
	static ShaderProgram3D * getShaderProgram3D(std::string);

private:
	static std::map<std::string, std::unique_ptr<ShaderProgram> > _shaderPrograms;
	static std::map<std::string, ShaderProgram3D *> _3DshaderPrograms;

};
