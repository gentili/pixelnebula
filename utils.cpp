#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;

void checkGLError() {
	auto glError = glGetError();
	if (glError != GL_NO_ERROR) {
		throw std::runtime_error("GL Error");
	}
}

void dumpmat(mat4x4 m) {
    float * fp = (float *) m;
    for (int i = 0; i < 16; i++) {
           cout << i << " : " << fixed << showpoint << setprecision(3) << fp[i] << endl;
    }
}

void dumpvec(vec3 v) {
    cout << v[0] << "," << v[1] << "," << v[2] << endl;

}

void dumpquat(quat q) {
    cout << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << endl;
}
