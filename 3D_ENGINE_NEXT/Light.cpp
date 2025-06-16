#include "Light.h"
COLORREF Light::globalColor = WHITE;
float Light::globalIntensity = 1;

Light::Light(COLORREF _color, float _intensity) 
    :color(_color), intensity(_intensity) {}

ParallelLight::ParallelLight(COLORREF _color, float _intensity, Vector _direction)
    : Light(_color, _intensity), direction(_direction) {}