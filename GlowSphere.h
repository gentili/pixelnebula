#pragma once

#include "Renderable.h"

class GlowSphere : public Renderable {
protected:
    GLuint _vertexAttrIndex_pos;
    GLuint _uniformIndex_color;
    GLuint _vbindexId;
    GLuint _vbposId;
    int _indexCount;
public:
    GlowSphere(float);

    virtual void draw();
};
