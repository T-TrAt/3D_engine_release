#include "LookupTable.h"

float LookupTable::sin[ANGLE_PRECISION];
float LookupTable::cos[ANGLE_PRECISION];

void LookupTable::init() {

    for (int i = 0; i < ANGLE_PRECISION; i += 1) {

        float angle = static_cast<float>(i) / 100.0f;
        sin[i] = std::sin(angle * PI / 180.0);
        cos[i] = std::cos(angle * PI / 180.0);
    }
}
float LookupTable::SIN(float angle) {

    angle = fmod(angle, 360.0f);	// 先取余，再控制正负，保证不出范围
    if (angle < 0) {
        angle += 360.0f;
    }
    return sin[static_cast<int>(angle * 100)];
}
float LookupTable::COS(float angle) {

    angle = fmod(angle, 360.0f);
    if (angle < 0) {
        angle += 360.0f;
    }
    return cos[static_cast<int>(angle * 100)];
}
