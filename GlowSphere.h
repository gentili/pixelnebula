#pragma once

#include "Renderable.h"

class GlowSphere : public Renderable {
protected:
    GLuint _vertexAttrIndex_pos;
    GLuint _uniformIndex_color;
    GLuint _vbindexId;
    GLuint _vbposId;
    int _indexCount;
    float _scale;
public:
    GlowSphere(float);

    virtual void draw();

    float getScale() {
        return _scale;
    }
};
