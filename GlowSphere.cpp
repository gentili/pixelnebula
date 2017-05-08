#include <vector>

#include "GlowSphere.h"
#include "utils.h"

GlowSphere::GlowSphere(float scale) 
    : Renderable("glowSphere"), _indexCount(0) {
    _vertexAttrIndex_pos = _shaderProgram->getAttributeLocation("pos");
    _uniformIndex_color = _shaderProgram->getUniformLocation("color");

    // Make square out of triangles
    vec3f v;
    std::vector<vec3f> vertexArray;
    std::vector<int> indexArray;

    // First half
    v.x = -0.5*scale;
    v.y = 0.5*scale;
    v.z = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = 0.5*scale;
    v.y = 0.5*scale;
    v.z = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = 0.5*scale;
    v.y = -0.5*scale;
    v.z = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    // Second half
    v.x = -0.5*scale;
    v.y = 0.5*scale;
    v.z = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = -0.5*scale;
    v.y = -0.5*scale;
    v.z = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = 0.5*scale;
    v.y = -0.5*scale;
    v.z = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    glGenBuffers(1,&_vbindexId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_vbindexId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indexArray[0])*indexArray.size(),
            &indexArray[0],
            GL_STATIC_DRAW);

    glGenBuffers(1,&_vbposId);
    glBindBuffer(GL_ARRAY_BUFFER,_vbposId);
    glBufferData(GL_ARRAY_BUFFER,
            sizeof(vertexArray[0])*vertexArray.size(),
            &vertexArray[0],
            GL_STATIC_DRAW);
}

void GlowSphere::draw() {
    _shaderProgram->setModelMatrix(_modelMatrix);

    glUniform4fv(_uniformIndex_color,1,&_color[0]);

    glBindBuffer(GL_ARRAY_BUFFER,_vbposId);
    glEnableVertexAttribArray(_vertexAttrIndex_pos);
    glVertexAttribPointer(_vertexAttrIndex_pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbindexId);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(_vertexAttrIndex_pos);
    glUseProgram(0);
}
