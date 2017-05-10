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
        vec4 tc = { 0.1f,0.1f,0.1f,0.0f };
        vec4_add(tc,c,tc);
        _innerPointStar.setColor(tc);
    }

    void setColor(float r, float g, float b, float a) {
		vec4 tc = { r,g,b,a };
        setColor(tc);
    }

    float * getColor() {
        return _outterPointStar.getColor();
    }

    void setTranslation(vec3 v) {
        _outterPointStar.setTranslation(v);
        _innerPointStar.setTranslation(v);
    }

    float * getTranslation() {
        return _outterPointStar.getTranslation();
    }

    void draw() {
        _outterPointStar.draw();
        _innerPointStar.draw();
    }
};
