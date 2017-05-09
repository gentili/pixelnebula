#pragma once

#include <vector>

#include "GlowSphere.h"
#include "DoublePointStar.h"

class Nebula {
private:
    static const float MAX_SPHERE;
    static const float CONTAINER_RADIUS;

    float _star_interpolation = 0.01;
    float _glow_interpolation = 0.1;

    std::vector<GlowSphere*> _gsarray;
    std::vector<DoublePointStar*> _dpsarray;
    vec4 _finalGlowColor;
    vec4 _finalStarColor;

    void setColor(DoublePointStar *);

    void setColor(GlowSphere *);

    void grow();

    void newStar();

    void newCloud();

    bool isTouching(vec3);

public:
    Nebula();

    void draw();

};
