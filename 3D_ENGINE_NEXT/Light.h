#pragma once
#include <easyx.h>
#include "Vector.h"
class Light{
public:
    static COLORREF globalColor;
    static float globalIntensity;

    COLORREF color;
    float intensity;

    Light(COLORREF _color, float _intensity);
};
class ParallelLight : public Light {
public:
    Vector direction;
    ParallelLight(COLORREF _color, float _intensity, Vector _direction);
};

