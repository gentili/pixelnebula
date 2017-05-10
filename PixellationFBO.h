#pragma once

#include "ShaderManager.h"

class PixellationFBO {
private:
    ShaderProgram* _shaderProgram;

    const int _pixellationFactor;
    const int _width;
    const int _height;

    GLuint _FBOid;
    GLuint _texBufId;
    GLuint _vertexAttrIndex_pos;
    GLuint _vertexAttrIndex_tex;
    GLuint _uniformIndex_scan_lines;
    GLuint _vbindexId;
    GLuint _vbposId;
    int _indexCount;

public:
    PixellationFBO(int,int,int);

    void begin();
    void end();
};
