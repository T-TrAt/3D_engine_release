#include "ModeController.h"
ModeController::ModeController()
    : mode(Mode::ControllingCamera), object(nullptr) {

    for (int i = 0; i < 256; i++) {
        keyStates[i] = KeyState::KEY_UP;
    }
}

// public
void ModeController::getMessage() {

    for (int i = 0; i < 256; i++) {
        updateKeyState(i); // ���°���״̬
    }
}

void ModeController::handleMessage() {

    switch (mode) {
    case Mode::ControllingCamera:
        handleMsg_Camera();
        break;
    case Mode::ControllingObjs:
        handleMsg_Objs();
        break;
    default:
        break;
    }
}

void ModeController::printInformation() {

    int line = 10;
    int height = line * Text::height;
    Orthogon background(5, SCREENH - 15 - height, SCREENW * 2 / 5, height + 10);
    background.frostedlyRend(2);
    background.colorFilt(0xEEEEEE);


    switch (mode) {
    case Mode::ControllingCamera:
        printInformation_Camera();
        break;
    case Mode::ControllingObjs:
        printInformation_Objs();
        break;
    default:
        break;
    }
}
// private
void ModeController::updateKeyState(int keyCode) {

    SHORT keyState = GetAsyncKeyState(keyCode);
    if (keyState & 0x8000) { // ����������
        if (keyStates[keyCode] == KeyState::KEY_UP) {
            keyStates[keyCode] = KeyState::KEY_DOWN; // �ոհ���
        }
        else {
            keyStates[keyCode] = KeyState::KEY_HELD; // ������ס
        }
    }
    else { // ����δ����
        keyStates[keyCode] = KeyState::KEY_UP;
    }
}

#define PRESS(x) (keyStates[(x)] == KeyState::KEY_DOWN || keyStates[(x)] == KeyState::KEY_HELD)
void ModeController::handleMsg_Camera() {

    if (PRESS('W'))      Camera::MOVE_FORWARD = true;
    if (PRESS('A'))      Camera::SLIDE_LEFT   = true;
    if (PRESS('S'))      Camera::MOVE_BACK    = true;
    if (PRESS('D'))      Camera::SLIDE_RIGHT  = true;
    if (PRESS(VK_UP))    Camera::LOOK_UP      = true;
    if (PRESS(VK_DOWN))  Camera::LOOK_DOWN    = true;
    if (PRESS(VK_LEFT))  Camera::LOOK_LEFT    = true;
    if (PRESS(VK_RIGHT)) Camera::LOOK_RIGHT   = true;
    if (PRESS(VK_SPACE)) Camera::UP           = true;
    if (PRESS(VK_SHIFT)) Camera::DOWN         = true;
    if (keyStates['1'] == KeyState::KEY_DOWN) mode = Mode::ControllingObjs;
}

#define MOVE_SPEED   (0.2)
#define ROTATE_SPEED (0.5)
void ModeController::handleMsg_Objs() {

    if (PRESS('W'))      object->moveFor(0.0, 0.0,  MOVE_SPEED);
    if (PRESS('S'))      object->moveFor(0.0, 0.0, -MOVE_SPEED);
    if (PRESS('A'))      object->moveFor(-MOVE_SPEED, 0.0, 0.0);
    if (PRESS('D'))      object->moveFor( MOVE_SPEED, 0.0, 0.0);
    if (PRESS(VK_SPACE)) object->moveFor(0.0,  MOVE_SPEED, 0.0);
    if (PRESS(VK_SHIFT)) object->moveFor(0.0, -MOVE_SPEED, 0.0);
    if (PRESS(VK_LEFT))  object->rotateFor(0.0,  ROTATE_SPEED, 0.0);
    if (PRESS(VK_RIGHT)) object->rotateFor(0.0, -ROTATE_SPEED, 0.0);
    if (keyStates['1'] == KeyState::KEY_DOWN) mode = Mode::ControllingCamera;
    if (keyStates['2'] == KeyState::KEY_DOWN) {
        int size = Shader::objects.size();
        objNum = (objNum + 1) % size;
        object = Shader::objects[objNum];
    }
}
#ifdef ROTATE_SPEED
#undef ROTATE_SPEED
#endif // ROTATE_SPEED
#ifdef MOVE_SPEED
#undef MOVE_SPEED
#endif // MOVE_SPEED
#ifdef PRESS(x)
#undef PRESS(x) 
#endif // PRESS(x)

void ModeController::printInformation_Camera() {

    Text position;
    Text viewDirection;
    Text cameraInformation;
    // �����λ����Ϣ��
    position.content << L"���λ�ã�" << std::setprecision(2)
                   << Camera::position.x << ", "
                   << Camera::position.y << ", "
                   << Camera::position.z;
    position.putText();

    // ��������Ϣ��
    viewDirection.content << L"����ͷ����" << std::setprecision(2)
                   << Camera::vwDrctn.x << ", "
                   << Camera::vwDrctn.y << ", "
                   << Camera::vwDrctn.z;
    viewDirection.putText();

    // ����ͷ�Ƕ���Ϣ��
    cameraInformation.content << L"����ͷ�Ƕȣ�" << std::setprecision(3)
                              << Camera::XZangle << ", " << Camera::YZangle;
    cameraInformation.putText();
}

void ModeController::printInformation_Objs() {

    // ����ѡ��ģ���߿�
    drawCubeFrame();

    Text objName;
    Text objPosition;
    Text objRotation;
    // ģ��������Ϣ��
    objName.content << L"ģ�����ƣ�" << object->name;
    objName.putText();
    // ģ��������Ϣ��
    objPosition.content << L"ģ�����꣺" << object->position.x 
                              << L", " << object->position.y 
                              << L", " << object->position.z;
    objPosition.putText();
    // ģ����ת��Ϣ��
    objRotation.content << L"ģ����ת�Ƕȣ�" << object->xAngle
                                  << L", " << object->yAngle
                                  << L", " << object->zAngle;
    objRotation.putText();
}

void ModeController::drawCubeFrame() {
    if (object == nullptr) object = Shader::objects[objNum];
    for (int i = 0; i < 12; i++) {
        transform();
        drawLine_CubeFrame(&tempEdge[i][0], &tempEdge[i][1]);
    }
}

void ModeController::transform() {

    transformedCubeFrame = object->cubeFrame;
    for (int i = 0; i < 8; i++) {
        transformedCubeFrame.vertices[i] += object->position;
    }
    
    for (int i = 0; i < 8; i++) {
        transformedCubeFrame.vertices[i] -= Camera::position;
        transformedCubeFrame.vertices[i].rotateY(360.0f - Camera::YZangle);
        transformedCubeFrame.vertices[i].rotateX(360.0f - Camera::XZangle);
    }

    int count = 0;
    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;
        tempEdge[count][0] = transformedCubeFrame.vertices[i   ];
        tempEdge[count][1] = transformedCubeFrame.vertices[next];
        if (tempEdge[count][0].z < Shader::NCP && tempEdge[count][1].z < Shader::NCP) {
            count++;
            continue;
        }
        if (tempEdge[count][0].z < Shader::NCP) tempEdge[count][0] = Shader::approximateVertex(tempEdge[count][1], tempEdge[count][0]);
        if (tempEdge[count][1].z < Shader::NCP) tempEdge[count][1] = Shader::approximateVertex(tempEdge[count][0], tempEdge[count][1]);
        count++;
    }
    for (int i = 4; i < 8; i++) {
        int next = (i + 1) % 4 + 4;
        tempEdge[count][0] = transformedCubeFrame.vertices[i   ];
        tempEdge[count][1] = transformedCubeFrame.vertices[next];
        if (tempEdge[count][0].z < Shader::NCP && tempEdge[count][1].z < Shader::NCP) {
            count++;
            continue;
        }
        if (tempEdge[count][0].z < Shader::NCP) tempEdge[count][0] = Shader::approximateVertex(tempEdge[count][1], tempEdge[count][0]);
        if (tempEdge[count][1].z < Shader::NCP) tempEdge[count][1] = Shader::approximateVertex(tempEdge[count][0], tempEdge[count][1]);
        count++;
    }
    for (int i = 0; i < 4; i++) {
        int next = i + 4;
        tempEdge[count][0] = transformedCubeFrame.vertices[i   ];
        tempEdge[count][1] = transformedCubeFrame.vertices[next];
        if (tempEdge[count][0].z < Shader::NCP && tempEdge[count][1].z < Shader::NCP) {
            count++;
            continue;
        }
        if (tempEdge[count][0].z < Shader::NCP) tempEdge[count][0] = Shader::approximateVertex(tempEdge[count][1], tempEdge[count][0]);
        if (tempEdge[count][1].z < Shader::NCP) tempEdge[count][1] = Shader::approximateVertex(tempEdge[count][0], tempEdge[count][1]);
        count++;
    }

    for (int i = 0; i < 12; i++) {
        
        float z = tempEdge[i][0].z;
        tempEdge[i][0].x *= SCREEN_DISTANCE / z;
        tempEdge[i][0].y *= SCREEN_DISTANCE / z;
        
        z = tempEdge[i][1].z;
        tempEdge[i][1].x *= SCREEN_DISTANCE / z;
        tempEdge[i][1].y *= SCREEN_DISTANCE / z;
    }
}

void ModeController::drawLine_CubeFrame(Vector* v1, Vector* v2) {

    if (v1->z < Shader::NCP && v2->z < Shader::NCP) return;
    int dy = v2->y - v1->y;
    int dx = v2->x - v1->x;
    if (dx == 0) {
        if (v2->y < v1->y) {
            Vector* temp = v1;
            v1 = v2;
            v2 = temp;
            dx *= -1;
            dy *= -1;
        }
        float w1 = 1 / v1->z;
        float w2 = 1 / v2->z;
        float dw = w2 - w1;
        float gradientOfW = dw / dy;
        float x = v1->x;
        float w = w1;
        for (int y = static_cast<int>(v1->y); y <= v2->y; y++, w += gradientOfW) {
            float z = 1 / w;
            int newX = x + H_SCREENW;
            int newY = y + H_SCREENH;
            if (newX < 1 || newX > SCREENW - 1) break;
            if (newY > SCREENH - 1) break;
            if (newY < 1) {
                float distance = 1 - newY - 1;
                y += distance;
                w += distance * gradientOfW;
                continue;
            }
            if (z < Shader::zBuffer[newY * SCREENW + newX]) Shader::putPixel(newX, newY, WHITE);
        }
        return;
    }
    float k = static_cast<float>(dy) / static_cast<float>(dx);
    if (std::abs(k) >= 1) {     // ����ֵ���ڵ���1����y�������
        if (v2->y < v1->y) {
            Vector* temp = v1;
            v1 = v2;
            v2 = temp;
            dx *= -1;
            dy *= -1;
        }
        float w1 = 1 / v1->z;
        float w2 = 1 / v2->z;
        float dw = w2 - w1;
        float gradientOfW = dw / dy;
        float x = v1->x;
        float w = w1;
        float _k = 1 / k;
        for (int y = static_cast<int>(v1->y); y <= v2->y; y++, x += _k, w += gradientOfW) {
            float z = 1 / w;
            int newX = x + H_SCREENW;
            int newY = y + H_SCREENH;
            if (newX < 1 || newX > SCREENW - 1) continue;
            if (newY > SCREENH - 1) break;
            if (newY < 1) {
                float distance = 1 - newY - 1;
                y += distance;
                x += distance * _k;
                w += distance * gradientOfW;
                continue;
            }
            if (z < Shader::zBuffer[newY * SCREENW + newX]) Shader::putPixel(newX, newY, WHITE);
        }
    }
    else {                      // �������x�������
        if (v2->x < v1->x) {
            Vector* temp = v1;
            v1 = v2;
            v2 = temp;
            dx *= -1;
            dy *= -1;
        }
        float w1 = 1 / v1->z;
        float w2 = 1 / v2->z;
        float dw = w2 - w1;
        float gradientOfW = dw / dx;
        float y = v1->y;
        float w = w1;
        for (int x = static_cast<int>(v1->x); x <= v2->x; x++, y += k, w += gradientOfW) {
            float z = 1 / w;
            int newX = x + H_SCREENW;
            int newY = y + H_SCREENH;
            if (newY < 1 || newY > SCREENH - 1) continue;
            if (newX > SCREENW - 1) break;
            if (newX < 1) {
                float distance = 1 - newX - 1;
                x += distance;
                y += distance * k;
                w += distance * gradientOfW;
                continue;
            }
            if (z < Shader::zBuffer[newY * SCREENW + newX]) Shader::putPixel(newX, newY, WHITE);
        }
    }
}