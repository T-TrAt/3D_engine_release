#pragma once
#include <unordered_map>
#include <cmath>
#define PI 3.141592f
#define ANGLE_PRECISION 36000

class LookupTable {
public:

    static float sin[ANGLE_PRECISION];
    static float cos[ANGLE_PRECISION];

    static void init();
    static float SIN(float angle);
    static float COS(float angle);
};