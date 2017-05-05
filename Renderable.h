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
            _shaderProgram = ShaderManager::getShaderProgram3D(shaderProgramName);
            mat4x4_identity(_modelMatrix);
	}

        void setTranslation(float x, float y, float z) {
            _position[0] = x;
            _position[1] = y;
            _position[2] = z;
            mat4x4_translate(_modelMatrix,x,y,z);
        }

        virtual void draw() = 0;
};
