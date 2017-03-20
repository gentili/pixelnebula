#include "Perspective.h"

void Camera::lookAtTarget() {
	mat4x4_look_at(_viewMatrix, _position, _target, _worldUpVector);

}