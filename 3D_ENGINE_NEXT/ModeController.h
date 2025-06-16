#pragma once
#include <unordered_map>
#include <easyx.h>
#include <iomanip>
#include "Text.h"
#include "Shader.h"
enum class Mode {
    ControllingCamera,
    ControllingObjs
};
enum class KeyState {
    KEY_UP,         // 按键未按下
    KEY_DOWN,       // 按键刚刚按下
    KEY_HELD        // 按键持续按住
};
class ModeController {
public:
    Mode mode;
    std::unordered_map<int, KeyState> keyStates;

    ModeController();
    void getMessage();
    void handleMessage();
    void printInformation();
private:
    void updateKeyState(int keyCode);

    void handleMsg_Camera();
    void printInformation_Camera();
    
    void handleMsg_Objs();
    Object*   object;
    int       objNum = 0;
    CubeFrame transformedCubeFrame;
    Vector    tempEdge[12][2];
    void printInformation_Objs();
private:
    void drawCubeFrame();
    void transform();
    void drawLine_CubeFrame(Vector* v1, Vector* v2);
};