#pragma once

#include <linmath.h>

class Projection {
private:
	mat4x4 _projectionMatrix;

public:
	void fromPerspective(float fovy, float aspect, float zNear, float zFar) {
		mat4x4_perspective(_projectionMatrix, fovy, aspect, zNear, zFar);
	}
	mat4x4 & asMatrix() { return _projectionMatrix; }
};

class Camera {
private:
	vec3 _position;
	vec3 _target;
	vec3 _worldUpVector;

	mat4x4 _viewMatrix;

public:
	mat4x4 & asMatrix() { return _viewMatrix; }

	void setUpVector(float x, float y, float z) {
		_worldUpVector[0] = x;
		_worldUpVector[1] = y;
		_worldUpVector[2] = z;
	}

	void setTarget(float x, float y, float z) {
		_target[0] = x;
		_target[1] = y;
		_target[2] = z;
	}

	void setPosition(float x, float y, float z) {
		_position[0] = x;
		_position[1] = y;
		_position[2] = z;
	}

	void lookAtTarget() {
            mat4x4_look_at(_viewMatrix, _position, _target, _worldUpVector);
        }
};
