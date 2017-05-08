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

        vec4 _color;
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

        void setTranslation(vec3 v) {
            _position[0] = v[0];
            _position[1] = v[1];
            _position[2] = v[2];
        }

        virtual void draw() = 0;

        void setColor(vec4 c) {
            _color[0] = c[0];
            _color[1] = c[1];
            _color[2] = c[2];
            _color[3] = c[3];
        }
};
