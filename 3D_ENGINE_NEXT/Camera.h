#pragma once
#include "Vector.h"
class Camera {
public:
    static Vector position;	                    // 相机位置
    static Vector vwDrctn;	                    // 方向

    static bool   MOVE_FORWARD, MOVE_BACK,
                  SLIDE_LEFT,   SLIDE_RIGHT,
                  LOOK_UP,      LOOK_DOWN,
                  LOOK_LEFT,    LOOK_RIGHT,
                  UP,           DOWN;     // 相机的十个运动状态

    static float  XZangle;	                    // 面朝角度
    static float  YZangle;

    static float  turnRate;	                    // 每帧刷新视角改变角度
    static float  moveSpeed;

    static void   init(float _x, float _y, float _z);
    static void   update();

};

