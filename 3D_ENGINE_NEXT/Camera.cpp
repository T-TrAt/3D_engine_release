#include "Camera.h"

Vector Camera::position(0.0, 0.0, 0.0); // 相机位置
Vector Camera::vwDrctn(0.0, 0.0, 1.0);  // 方向

bool Camera::MOVE_FORWARD = false,
     Camera::MOVE_BACK    = false,
     Camera::SLIDE_LEFT   = false,
     Camera::SLIDE_RIGHT  = false,
     Camera::LOOK_UP      = false,
     Camera::LOOK_DOWN    = false,
     Camera::LOOK_LEFT    = false,
     Camera::LOOK_RIGHT   = false,
     Camera::UP           = false,
     Camera::DOWN         = false; // 相机的十个运动状态

float Camera::XZangle = 0.0f;    // 面朝角度, xz平面角度与yz平面角度
float Camera::YZangle = 0.0f;

float Camera::turnRate  = 2.0f;  // 每帧刷新视角改变角度
float Camera::moveSpeed = 0.06f;

void Camera::init(float _x, float _y, float _z) {

    position.set(_x, _y, _z);
    vwDrctn.set(0.0, 0.0, 1.0);
}

void Camera::update() {

    if (LOOK_UP) {

        XZangle += turnRate;
        if (XZangle < 0) XZangle += 360.0f;
        if (XZangle >= 90.0 && XZangle <= 270.0) {
            XZangle = 89.99f;
        }
    }
    if (LOOK_DOWN) {

        XZangle -= turnRate;
        if (XZangle < 0) XZangle += 360.0f;
        if (XZangle >= 90.0 && XZangle <= 270.0) {
            XZangle = 270.01f;
        }
    }
    if (LOOK_LEFT) {

        YZangle -= turnRate;
    }
    if (LOOK_RIGHT) {

        YZangle += turnRate;
    }
    
    XZangle = std::fmod(XZangle, 360.0f);	// 限制角度
    YZangle = std::fmod(YZangle, 360.0f);
    vwDrctn.set(0.0, 0.0, 1.0);
    vwDrctn.rotateX(XZangle);	// 先绕x轴再绕y轴
    vwDrctn.rotateY(YZangle);
    vwDrctn.unit();

    if (MOVE_FORWARD) {
        vwDrctn.y = 0;
        vwDrctn.unit();
        position.add(vwDrctn, moveSpeed);
    }
    if (MOVE_BACK) {
        vwDrctn.y = 0;
        vwDrctn.unit();
        position.sub(vwDrctn, moveSpeed);
    }
    if (SLIDE_LEFT) {
        Vector left(vwDrctn.cross(Vector(0.0, 1.0, 0.0)));
        left.unit();
        position.add(left, moveSpeed);
    }
    if (SLIDE_RIGHT) {
        Vector right(vwDrctn.cross(Vector(0.0, -1.0, 0.0)));
        right.unit();
        position.add(right, moveSpeed);
    }
    if (UP) {
        Vector up(0.0, 1.0, 0.0);
        position.add(up, moveSpeed);
    }
    if (DOWN) {
        Vector down(0.0, -1.0, 0.0);
        position.add(down, moveSpeed);
    }

    // 状态量归位
    MOVE_FORWARD = false;
    MOVE_BACK    = false;
    SLIDE_LEFT   = false;
    SLIDE_RIGHT  = false;
    LOOK_UP      = false;
    LOOK_DOWN    = false;
    LOOK_LEFT    = false;
    LOOK_RIGHT   = false;
    UP           = false;
    DOWN         = false;
}