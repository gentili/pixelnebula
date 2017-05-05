#include "Axis.h"
#include "utils.h"

GLuint vbindex[] = {
    0,
    1,
    2,
    3,
    4,
    5
};

GLfloat vbpos[] = {
    0,0,0,
    1,0,0, // X Axis
    0,0,0,
    0,1,0, // Y Axis
    0,0,0,
    0,0,1  // Z Axis
};

GLfloat vbcolor[] = {
    0.1,0,0,1,
      1,0,0,1, // X Axis RED
    0,0.1,0,1,
    0,  1,0,1, // Y Axis GREEN
    0,0,0.1,1,
    0,0,  1,1  // Z Axis BLUE
};

GLuint Axis::_vertexAttrIndex_pos;
GLuint Axis::_vertexAttrIndex_color;
GLuint Axis::_vbindexId;
GLuint Axis::_vbposId;
GLuint Axis::_vbcolorId;
bool Axis::_init = false;

Axis::Axis() : Renderable("simpleIndexedColor") {
    if (_init)
        return;
    _init = true;

    _vertexAttrIndex_pos = _shaderProgram->getAttributeLocation("pos");
    _vertexAttrIndex_color = _shaderProgram->getAttributeLocation("color");

    glGenBuffers(1,&_vbindexId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_vbindexId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vbindex),vbindex,GL_STATIC_DRAW);

    glGenBuffers(1,&_vbposId);
    glBindBuffer(GL_ARRAY_BUFFER,_vbposId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vbpos),vbpos,GL_STATIC_DRAW);

    glGenBuffers(1,&_vbcolorId);
    glBindBuffer(GL_ARRAY_BUFFER,_vbcolorId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vbcolor),vbcolor,GL_STATIC_DRAW);
};

void Axis::draw() {
    _shaderProgram->setModelMatrix(_modelMatrix);

    glBindBuffer(GL_ARRAY_BUFFER,_vbposId);
    checkGLError();
    glEnableVertexAttribArray(_vertexAttrIndex_pos);
    checkGLError();
    glVertexAttribPointer(_vertexAttrIndex_pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
    checkGLError();

    glBindBuffer(GL_ARRAY_BUFFER,_vbcolorId);
    checkGLError();
    glEnableVertexAttribArray(_vertexAttrIndex_color);
    checkGLError();
    glVertexAttribPointer(_vertexAttrIndex_color, 4, GL_FLOAT, GL_FALSE, 0, 0);
    checkGLError();

    glBindBuffer(GL_ARRAY_BUFFER,0);
    checkGLError();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbindexId);
    checkGLError();
    glDrawElements(GL_LINES, sizeof(vbindex)/sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
    checkGLError();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    checkGLError();
    glDisableVertexAttribArray(_vertexAttrIndex_pos);
    checkGLError();
    glUseProgram(0);
    checkGLError();

};
