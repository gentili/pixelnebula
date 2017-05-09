#include "Nebula.h"
#include "utils.h"

const float Nebula::MAX_SPHERE = 1;
const float Nebula::CONTAINER_RADIUS = 2;

Nebula::Nebula() {
    vec3 v = {1,1,1};
    vec3_norm(v,v);
    vec3_scale(v,v,CONTAINER_RADIUS);
    dumpvec(v);

    GlowSphere* gs = new GlowSphere(MAX_SPHERE);
    gs->setTranslation(v);
    setColor(gs);
    _gsarray.push_back(gs);

    DoublePointStar* dps = new DoublePointStar(0.2);
    dps->setTranslation(v);
    setColor(dps);
    _dpsarray.push_back(dps);

    vec3_scale(v,v,-1);
    gs = new GlowSphere(MAX_SPHERE);
    gs->setTranslation(v);
    setColor(gs);
    _gsarray.push_back(gs);

    dps = new DoublePointStar(0.2);
    dps->setTranslation(v);
    setColor(dps);
    _dpsarray.push_back(dps);
}

void Nebula::setColor(DoublePointStar * dps) {
    float* v = (dps->getTranslation());
    float red = (CONTAINER_RADIUS + v[1])/(2*CONTAINER_RADIUS);
    float mag = 0.5;
    dps->setColor(red*mag, 0, mag, 0);
}

void Nebula::setColor(GlowSphere * gs) {
    float* v = (gs->getTranslation());
    float red = (CONTAINER_RADIUS + v[1])/(2*CONTAINER_RADIUS);
    float mag = 0.1;
    gs->setColor(red*mag, 0, mag, 0);
}

void Nebula::draw() {
    for (auto dpsitr = _dpsarray.begin();
            dpsitr != _dpsarray.end();
            dpsitr++)
        (*dpsitr)->draw();
    for (auto gsitr = _gsarray.begin();
            gsitr != _gsarray.end();
            gsitr++) 
        (*gsitr)->draw();
}
