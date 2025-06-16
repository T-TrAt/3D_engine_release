#pragma once
#include "Shader.h"
#include <easyx.h>
class Orthogon {
public:
    RECT rect;

    Orthogon();
    Orthogon(RECT& r);
    Orthogon(int x, int y, int width, int height);

    void frostedlyRend(int scalar); // Ä¥É°Ìî³ä
    void colorFilt(COLORREF color); // É«²ÊÂË¾µ
private:
    COLORREF frostBlend(int x, int y, int range);
};

class Botton {
public:

};
