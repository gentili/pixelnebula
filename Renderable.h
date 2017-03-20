#pragma once

#include <string>

#include "ShaderManager.h"

#include <linmath.h>

class Renderable {
protected:
	ShaderProgram3D * _shaderProgram = nullptr;

	vec3 _position;
	vec3 _rotationAxis;
	float _rotationMag;
	vec3 _scale;

	mat4x4 _modelMatrix;
public:
	Renderable(std::string shaderProgramName) {
		if (_shaderProgram == nullptr) {
			_shaderProgram = ShaderManager::getShaderProgram3D(shaderProgramName);
		}
		GLuint _vertexAttrIndex_pos = _shaderProgram->getAttributeLocation("pos");
		GLuint _vertexAttrIndex_color = _shaderProgram->getAttributeLocation("color");
	};

};