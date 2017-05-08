#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <linmath.h>

#include "Renderable.h"
#include "utils.h"


class PointStar : public Renderable {
protected:
    GLuint _vertexAttrIndex_pos;
    GLuint _uniformIndex_color;
    GLuint _vbindexId;
    GLuint _vbposId;
    int _indexCount;
public:
    PointStar(float);

    virtual void draw();

private:
    void addTriangle(quat & Q,
            std::vector<vec3f> & vertexArray,
            std::vector<int> & indexArray,
            int & curindex,
            vec3 & vertexA,
            vec3 & vertexB,
            vec3 & vertexC);
            
};
