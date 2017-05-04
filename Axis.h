#pragma once

#include <string>

#include "Renderable.h"

#include <linmath.h>

#include <iostream>

class Axis : public Renderable {
protected:
    static bool _init;
    static GLuint _vertexAttrIndex_pos;
    static GLuint _vertexAttrIndex_color;
    static GLuint _vbindexId;
    static GLuint _vbposId;
    static GLuint _vbcolorId;
public:
    Axis();

    virtual void draw();
};
