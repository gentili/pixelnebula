#include "PointStar.h"
#include "utils.h"
#include <cmath>

PointStar::PointStar(float scale) : Renderable("concursionPoint") {
    _vertexAttrIndex_pos = _shaderProgram->getAttributeLocation("pos");
    _uniformIndex_color = _shaderProgram->getUniformLocation("color");

    vec3 vertexA;
    vertexA[0] = -0.5f*scale;
    vertexA[1] = 0;
    vertexA[2] = 0;

    vec3 vertexB;
    vertexB[0] = 0.5f*scale;
    vertexB[1] = 0;
    vertexB[2] = 0;

    vec3 vertexC;
    vertexC[0] = 0;
    vertexC[1] = 1*scale;
    vertexC[2] = 0;

    vec3 unitZ = {0,0,1};

    quat zeroQ;
    quat_rotate(zeroQ,0,unitZ);

    quat halfpiQ;
    quat_rotate(halfpiQ,M_PI_2,unitZ);

    quat piQ;
    quat_rotate(piQ,M_PI,unitZ);

    quat minushalfpiQ;
    quat_rotate(minushalfpiQ,-M_PI_2,unitZ);

    std::vector<vec3f> vertexArray;
    std::vector<int> indexArray;

    _indexCount = 0;

    for (int i = 0; i < 4; i++) {
        addTriangle(zeroQ,vertexArray,indexArray,_indexCount,vertexA,vertexB,vertexC);
        addTriangle(halfpiQ,vertexArray,indexArray,_indexCount,vertexA,vertexB,vertexC);
        addTriangle(piQ,vertexArray,indexArray,_indexCount,vertexA,vertexB,vertexC);
        addTriangle(minushalfpiQ,vertexArray,indexArray,_indexCount,vertexA,vertexB,vertexC);
        vertexA[0] *= 0.6f;
        vertexB[0] *= 0.6f;
        vertexC[1] *= 1.5;
    }
    
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
};

void PointStar::addTriangle(quat & Q,
            std::vector<vec3f> & vertexArray,
            std::vector<int> & indexArray,
            int & curindex,
            vec3 & vertexA,
            vec3 & vertexB,
            vec3 & vertexC) {
    vec3 v;

    quat_mul_vec3(v,Q,vertexA);
    vertexArray.push_back(v);
    indexArray.push_back(curindex++);

    quat_mul_vec3(v,Q,vertexB);
    vertexArray.push_back(v);
    indexArray.push_back(curindex++);

    quat_mul_vec3(v,Q,vertexC);
    vertexArray.push_back(v);
    indexArray.push_back(curindex++);
}


void PointStar::draw() {
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
};
