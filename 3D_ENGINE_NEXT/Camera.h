#pragma once
#include "Vector.h"
class Camera {
public:
    static Vector position;	                    // ���λ��
    static Vector vwDrctn;	                    // ����

    static bool   MOVE_FORWARD, MOVE_BACK,
                  SLIDE_LEFT,   SLIDE_RIGHT,
                  LOOK_UP,      LOOK_DOWN,
                  LOOK_LEFT,    LOOK_RIGHT,
                  UP,           DOWN;     // �����ʮ���˶�״̬

    static float  XZangle;	                    // �泯�Ƕ�
    static float  YZangle;

    static float  turnRate;	                    // ÿ֡ˢ���ӽǸı�Ƕ�
    static float  moveSpeed;

    static void   init(float _x, float _y, float _z);
    static void   update();

};

