#pragma once

#include "PointStar.h"

class DoublePointStar {
private: 
    PointStar _outterPointStar;
    PointStar _innerPointStar;

public:
    DoublePointStar(float scale) : 
        _outterPointStar(scale), 
        _innerPointStar(scale/2.5f) {
    }

    void setColor(vec4 c) {
        _outterPointStar.setColor(c);
        vec4 tc;
        vec4_add(tc,c,(vec4){0.1,0.1,0.1,0});
        _innerPointStar.setColor(tc);
    }

    void setTranslation(vec3 v) {
        _outterPointStar.setTranslation(v);
        _innerPointStar.setTranslation(v);
    }

    void draw() {
        _outterPointStar.draw();
        _innerPointStar.draw();
    }
};
