#include "Widget.h"
Orthogon::Orthogon()
    : rect({ 0, 0, 100, 100 }) {}

Orthogon::Orthogon(RECT& r)
    : rect(r) {}

Orthogon::Orthogon(int x, int y, int width, int height)
    : rect({ x, y + height, x + width, y }) {}

void Orthogon::frostedlyRend(int scalar) {

    int left   = max(rect.left  , 1);
    int right  = min(rect.right , SCREENW - 1);
    int bottom = max(rect.bottom, 1);
    int top    = min(rect.top   , SCREENH - 1);
    for (int y = bottom; y <= top; y++) {
        for (int x = left; x <= right; x++) {

            Shader::putPixel(x, y, frostBlend(x, y, scalar));
        }
    }
}

void Orthogon::colorFilt(COLORREF color) {

    int cR = (color) & 0xFF;
    int cG = (color >> 8) & 0xFF;
    int cB = (color >> 16) & 0xFF;
    int left = max(rect.left, 1);
    int right = min(rect.right, SCREENW - 1);
    int bottom = max(rect.bottom, 1);
    int top = min(rect.top, SCREENH - 1);
    for (int y = bottom; y <= top; y++) {
        for (int x = left; x <= right; x++) {

            float scalar;
            COLORREF thisColor = Shader::getPixel(x, y);
            int B = (thisColor)       & 0xFF;
            int G = (thisColor >> 8)  & 0xFF;
            int R = (thisColor >> 16) & 0xFF;

            scalar = static_cast<float>(cB) / 0xFF;
            B *= scalar;
            scalar = static_cast<float>(cG) / 0xFF;
            G *= scalar;
            scalar = static_cast<float>(cR) / 0xFF;
            R *= scalar;

            thisColor = (R) | (G << 8) | (B << 16);
            Shader::putPixel(x, y, thisColor);
        }
    }
}

COLORREF Orthogon::frostBlend(int x, int y, int range) {

    int R = 0;
    int G = 0;
    int B = 0;
    int r = range * 2;
    int left   = max(x - r, 1);
    int right  = min(x + r, SCREENW - 1);
    int bottom = max(y - r, 1);
    int top    = min(y + r, SCREENH - 1);
    int count  = 0;
    for (int i = bottom; i <= top; i += 2) {
        for (int j = left; j <= right; j += 2) {

            COLORREF color = Shader::getPixel(j, i);
            B += (color)       & 0xFF;
            G += (color >> 8)  & 0xFF;
            R += (color >> 16) & 0xFF;
            count++;
        }
    }
    B /= count;
    G /= count;
    R /= count;

    COLORREF color = (R) | (G << 8) | (B << 16);
    return color;
}