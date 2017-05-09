#pragma once

#include <linmath.h>

#include "utils.h"

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
	vec3 _worldUpVector;
	vec3 _target;
        float _rad;
        float _rot;

	mat4x4 _viewMatrix;

public:
	mat4x4 & asMatrix() { return _viewMatrix; }

	void setUpVector(float x, float y, float z) {
		_worldUpVector[0] = x;
		_worldUpVector[1] = y;
		_worldUpVector[2] = z;
                vec3_norm(_worldUpVector,_worldUpVector);
	}

	void setTarget(float x, float y, float z) {
		_target[0] = x;
		_target[1] = y;
		_target[2] = z;
	}

        void setRotation(float rot) {
            _rot = rot;
        }
        
        float getRotation() {
            return _rot;
        }

        void addRotation(float rot) {
            _rot += rot;
        }

        void setRadius(float rad) {
            _rad = rad;
        }

	void lookAtTarget() {
            vec3 pos = {0,0,_rad};
            quat q; 
            quat_rotate(q,_rot,_worldUpVector);
            quat_mul_vec3(pos,q,pos);

            mat4x4_look_at(_viewMatrix, pos, _target, _worldUpVector);
        }
};
