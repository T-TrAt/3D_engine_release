#pragma once
#include "Shader.h"
#include <easyx.h>
class Orthogon {
public:
    RECT rect;

    Orthogon();
    Orthogon(RECT& r);
    Orthogon(int x, int y, int width, int height);

    void frostedlyRend(int scalar); // ĥɰ���
    void colorFilt(COLORREF color); // ɫ���˾�
private:
    COLORREF frostBlend(int x, int y, int range);
};

class Botton {
public:

};
