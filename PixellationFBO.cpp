#include <iostream>
#include <vector>

#include "PixellationFBO.h"
#include "utils.h"

PixellationFBO::PixellationFBO(int width, int height, int pixellationFactor) :
        _pixellationFactor(pixellationFactor), 
        _width(width), 
        _height(height) {
    _shaderProgram = ShaderManager::getShaderProgram("scanLine");

    _vertexAttrIndex_pos = _shaderProgram->getAttributeLocation("pos");
    _vertexAttrIndex_tex = _shaderProgram->getAttributeLocation("tex");
    _uniformIndex_scan_lines = _shaderProgram->getUniformLocation("scan_lines");

    // Set up Framebuffer and attached buffers
    // Setup the texture buffer
    glGenTextures(1,&_texBufId);
    glBindTexture(GL_TEXTURE_2D, _texBufId);
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        _width/pixellationFactor,
        _height/pixellationFactor,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Setup the depth buffer
    GLuint RBdepthId;
    glGenRenderbuffers(1,&RBdepthId);
    glBindRenderbuffer(GL_RENDERBUFFER,RBdepthId);
    glRenderbufferStorage(GL_RENDERBUFFER,
            GL_DEPTH_COMPONENT,
            _width/_pixellationFactor,
            _height/_pixellationFactor);
    glBindRenderbuffer(GL_RENDERBUFFER,0);

    // Setup the frame buffer object
    glGenFramebuffers(1,&_FBOid);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBOid);

    // Attach the texture
    glFramebufferTexture2D(GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            _texBufId,
            0);

    // Attach the depth buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER,
            RBdepthId);

    // Verify status
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
            GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("framebuffer setup failed");
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);

    // Make square out of triangles
    _indexCount = 0;
    texvec v;
    std::vector<texvec> vertexArray;
    std::vector<int> indexArray;

    // First half
    v.x = -1;
    v.y = 1;
    v.z = 0;
    v.s = 0;
    v.t = 1;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = 1;
    v.y = 1;
    v.z = 0;
    v.s = 1;
    v.t = 1;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = 1;
    v.y = -1;
    v.z = 0;
    v.s = 1;
    v.t = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    // Second half
    v.x = -1;
    v.y = 1;
    v.z = 0;
    v.s = 0;
    v.t = 1;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = -1;
    v.y = -1;
    v.z = 0;
    v.s = 0;
    v.t = 0;
    vertexArray.push_back(v);
    indexArray.push_back(_indexCount++);

    v.x = 1;
    v.y = -1;
    v.z = 0;
    v.s = 1;
    v.t = 0;
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
};

void PixellationFBO::begin() {
    glBindFramebuffer(GL_FRAMEBUFFER, _FBOid);
    glViewport(0,0,_width/_pixellationFactor,_height/_pixellationFactor);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void PixellationFBO::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,_width,_height);

    // Texture render
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glUseProgram(_shaderProgram->getId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_texBufId);

    glUniform1i(_uniformIndex_scan_lines,_pixellationFactor);

    // bind array buffer
    glBindBuffer(GL_ARRAY_BUFFER,_vbposId);

    // set up position
    glEnableVertexAttribArray(_vertexAttrIndex_pos);
    glVertexAttribPointer(_vertexAttrIndex_pos, 3, GL_FLOAT, GL_FALSE, 
            sizeof(texvec), 0);

    // set up texture
    glEnableVertexAttribArray(_vertexAttrIndex_tex);
    glVertexAttribPointer(_vertexAttrIndex_tex, 2, GL_FLOAT, GL_FALSE, 
            sizeof(texvec), (void*)(12));

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbindexId);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(_vertexAttrIndex_pos);
    glDisableVertexAttribArray(_vertexAttrIndex_tex);
    glUseProgram(0);
    
}
