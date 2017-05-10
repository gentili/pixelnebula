#include <cfloat>

#include "Nebula.h"
#include "utils.h"

const float Nebula::MAX_SPHERE = 1;
const float Nebula::CONTAINER_RADIUS = 2;

Nebula::Nebula() {
    vec3 v = {1,1,1};
    vec3_norm(v,v);
    vec3_scale(v,v,CONTAINER_RADIUS);

    GlowSphere* gs = new GlowSphere(MAX_SPHERE);
    gs->setTranslation(v);
    setColor(gs);
    vec4_norm(gs->getColor(),gs->getColor());
    vec4_scale(gs->getColor(),gs->getColor(),0.2f);
    _gsarray.push_back(gs);

    DoublePointStar* dps = new DoublePointStar(0.2f);
    dps->setTranslation(v);
    setColor(dps);
    _dpsarray.push_back(dps);

    vec3_scale(v,v,-1);

    gs = new GlowSphere(MAX_SPHERE);
    gs->setTranslation(v);
    setColor(gs);
    vec4_norm(gs->getColor(),gs->getColor());
    vec4_scale(gs->getColor(),gs->getColor(),0.2f);
    _gsarray.push_back(gs);

    dps = new DoublePointStar(0.2f);
    dps->setTranslation(v);
    setColor(dps);
    _dpsarray.push_back(dps);
}

void Nebula::setColor(DoublePointStar * dps) {
    float* v = (dps->getTranslation());
    float red = (CONTAINER_RADIUS + v[1])/(2*CONTAINER_RADIUS);
    float mag = 0.1f;
    dps->setColor(red*mag, 0, mag, 0);
}

void Nebula::setColor(GlowSphere * gs) {
    float* v = (gs->getTranslation());
    float red = (CONTAINER_RADIUS + v[1])/(2*CONTAINER_RADIUS);
    float mag = 0.05f;
    gs->setColor(red*mag, 0, mag, 0);
}

void Nebula::draw() {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE,GL_ONE);
    glBlendEquation(GL_FUNC_ADD);
    grow();
    for (auto dpsitr = _dpsarray.begin();
            dpsitr != _dpsarray.end();
            dpsitr++)
        (*dpsitr)->draw();
    for (auto gsitr = _gsarray.begin();
            gsitr != _gsarray.end();
            gsitr++) 
        (*gsitr)->draw();
}

void Nebula::grow() {
    if (_dpsarray.size() < 31) {
        // auto dps = _dpsarray[_dpsarray.size()-1];
        newStar();
        if (_dpsarray.size() == 31)
            std::cout << "Final star generated" << std::endl;
    } else
    if (_gsarray.size() < 400) {
        newCloud();
        if (_gsarray.size() == 400)
            std::cout << "Final glowsphere generated" << std::endl;
    }
}

void Nebula::newStar() {
    // Direction
    vec3 dir = {randfloat()-0.5f,randfloat()-0.5f,randfloat()-0.5f};
    vec3_norm(dir,dir);

    // Magnitude
    float mag = randfloat() - 0.5f + CONTAINER_RADIUS;
    vec3_scale(dir,dir,mag);

    // Size
    float size = randfloat()*0.07f+0.01f;

    // Make star
    auto dps = new DoublePointStar(size);
    dps->setTranslation(dir);
    setColor(dps);
    _dpsarray.push_back(dps);

    // Make glow sphere
    auto gs = new GlowSphere(size*10);
    gs->setTranslation(dir);
    setColor(gs);
    vec4_norm(gs->getColor(),gs->getColor());
    vec4_scale(gs->getColor(),gs->getColor(),0.2f);
    _gsarray.push_back(gs);
}

void Nebula::newCloud() {
    while(true) {
        // Direction
        vec3 dir = {randfloat()-0.5f,randfloat()-0.5f,randfloat()-0.5f};
        vec3_norm(dir,dir);

        // Magnitude
        float mag = randfloat() - 0.5f + CONTAINER_RADIUS;
        vec3_scale(dir,dir,mag);

        // Reject points already inside a nebula
        if (isTouching(dir))
            continue;

        // Start the random walk
        while(true) {
            // Direction
            vec3 randir = {randfloat()-0.5f,randfloat()-0.5f,randfloat()-0.5f};
            vec3_norm(randir,randir);
            vec3_scale(randir,randir,0.05f);
            vec3_add(dir,dir,randir);
            // If we walked out of the sphere then give up
            if (vec3_len(dir) > CONTAINER_RADIUS + 0.5)
                break;
            // If this sphere is touching another then it's good
            if (isTouching(dir)) {
                // We size the sphere based on distance to nearest star
                // making little tendrils
                float dist = FLT_MAX;
                for (auto dpsitr = _dpsarray.begin();
                        dpsitr != _dpsarray.end();
                        dpsitr++) {
                    float curdist = vec3_distance(dir,(*dpsitr)->getTranslation());
                    if (curdist < dist)
                        dist = curdist;
                }
                float size = 1 - dist;
                if (size < 0.05)
                    break;
                auto gs = new GlowSphere(size);
                gs->setTranslation(dir);
                setColor(gs);
                _gsarray.push_back(gs);
                return;
            }
        }
    }
}

bool Nebula::isTouching(vec3 v) {
    for (auto gsitr = _gsarray.begin();
            gsitr != _gsarray.end();
            gsitr++) {
        auto gs = *gsitr;
        if (vec3_distance(gs->getTranslation(),v) < gs->getScale()/1.7) {
            return true;
        }
    }
    return false;
}
