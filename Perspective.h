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
	quat _orientation;

	vec3 _worldUpVector;
	vec3 _target;
	float _radius;
	float _horizRads;
	float _vertRads;
	quat _rotAboutTarget;
	vec3 _posRelativeToTarget;

	mat4x4 _viewMatrix;

public:
	Camera();
};