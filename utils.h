#pragma once

#include<cstdlib>

#include "deps/linmath.h"

class vec3f {
    public:
        float x,y,z;
        vec3f() { 
            x=y=z=0; 
        }
        vec3f(vec3 v) {
            x = v[0];
            y = v[1];
            z = v[2];
        }
        vec3f & operator*=(float rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
};

void checkGLError();

void dumpmat(mat4x4 m);

void dumpvec(vec3 v);

void dumpquat(quat q);

float randfloat();

float vec3_distance(vec3, vec3);
