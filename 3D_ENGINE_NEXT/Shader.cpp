#include "Shader.h"

std::vector<Object*> Shader::objects;
DWORD* Shader::pMem;

float Shader::NCP = 0.3f;               // ������ƽ���λ��
float Shader::FCP = 1000;            // ��ʼ��zBufferʹ�õ���Զ����

float* Shader::zBuffer;

Shader::Shader(int type) {    
    pMem = GetImageBuffer();
    zBuffer = new float[SCREEN_SIZE];
    for (int i = 0; i < SCREEN_SIZE; i++) zBuffer[i] = FCP;
    for (int i = 0; i < SCREENH; i++)     xStart[i]  = SCREENW;
    for (int i = 0; i < SCREENH; i++)     xEnd[i]    = 0;
    for (int i = 0; i < SCREENH; i++)     wStart[i]  = FCP;
    for (int i = 0; i < SCREENH; i++)     wEnd[i]    = FCP;

    bottomOfScan = SCREENH;
    topOfScan = 0;
    
    renderingType = type;
}

Vector Shader::approximateVertex(Vector p1, Vector p2) {    // p1 ����һ���㣬p2 ����һ����
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float dz     = p2.z - p1.z;
    float new_dz = NCP  - p1.z; // �µ���ϵ��z��

    float scalar = new_dz / dz; // ���Բ�ֵ��ϵ��

    float newX = p1.x + dx * scalar;
    float newY = p1.y + dy * scalar;

    return Vector(newX, newY, NCP);
}

void Shader::culculateFaceNormals() {
    int faceIndex = 0;
    for (int i = 0; i < object->numIndices; i += 3, faceIndex++) {

        Vector* p1 = &object->transformedVertices[object->indices[i    ]];
        Vector* p2 = &object->transformedVertices[object->indices[i + 1]];
        Vector* p3 = &object->transformedVertices[object->indices[i + 2]];

        Vector v1 = *p2 - *p1;
        Vector v2 = *p3 - *p1;

        object->faceNormals[faceIndex] = Vector::cross(v1, v2);
    }
}

void Shader::localRotate() {
    for (int i = 0; i < object->numVertices; i++) {
        object->transformedVertices[i] = object->vertices[i];
    }

    for (int i = 0; i < object->numVertices; i++) {

        object->transformedVertices[i].rotateX(object->xAngle);
        object->transformedVertices[i].rotateY(object->yAngle);
        object->transformedVertices[i].rotateZ(object->zAngle);
    }
}

void Shader::translation() {
    for (int i = 0; i < object->numVertices; i++) {
        object->transformedVertices[i] += object->position;
    }
}

void Shader::cameraTransform() {
    for (int i = 0; i < object->numVertices; i++) {

        object->transformedVertices[i] -= Camera::position;
        object->transformedVertices[i].rotateY(360.0f - Camera::YZangle);
        object->transformedVertices[i].rotateX(360.0f - Camera::XZangle);
    }
}

void Shader::perspectiveTransform() {
    for (int i = 0; i < tempVerticesCount; i++) {

        float z = tempVertices[i].z;
        tempVertices[i].x *= SCREEN_DISTANCE / z;
        tempVertices[i].y *= SCREEN_DISTANCE / z;
    }
}

void Shader::drawWireFrame() {
    for (int i = 0; i < tempVerticesCount; i++) {

        int nextIndex = i + 1;
        if (nextIndex >= tempVerticesCount) nextIndex = 0;

        int x1 = tempVertices[i].x;
        int y1 = tempVertices[i].y;

        int x2 = tempVertices[nextIndex].x;
        int y2 = tempVertices[nextIndex].y;

        x1 += H_SCREENW;
        y1 += H_SCREENH;

        x2 += H_SCREENW;
        y2 += H_SCREENH;

        line(x1, y1, x2, y2);
    }
}

bool Shader::testHidden(int index) {
    bool haveToBeHidden = true;
    Vector p1 = object->transformedVertices[object->indices[index]];

    Vector direction = p1;
    Vector normal = object->faceNormals[index / 3];
    normal.rotateY(360.0f - Camera::YZangle);
    normal.rotateX(360.0f - Camera::XZangle);
    if (normal.dot(direction) > 0) return true;

    for (int i = index; i < index + 3; i++) {
        
        if (object->transformedVertices[object->indices[i]].z > NCP) {
            haveToBeHidden = false;
            return false;
        }
    }
    return haveToBeHidden;
}

bool Shader::clipNearPlane(int index) {

    tempVerticesCount = 3;
    bool haveToBeClipped = false;
    int outOfRegionCount = 0;

    int j = 0;
    for (int i = index; i < index + 3; i++) {

        if (object->transformedVertices[object->indices[i]].z < NCP) {

            haveToBeClipped = true;
            outOfRegionCount++;

            int nextIndex = i + 1;
            if (nextIndex > index + 2) nextIndex = index;       // �����ǵ��������㣬��һ�����ǵ�һ������
            
            if (object->transformedVertices[object->indices[nextIndex]].z < NCP) continue;   // �����㶼���ã�������

            tempVertices[j] = approximateVertex(object->transformedVertices[object->indices[i        ]],
                                                object->transformedVertices[object->indices[nextIndex]]);
            j++;
        }
        else {
            tempVertices[j] = object->transformedVertices[object->indices[i]];   // �����þͰ�˳������
            j++;

            int nextIndex = i + 1;
            if (nextIndex > index + 2) nextIndex = index;       // �����ǵ��������㣬��һ�����ǵ�һ������

            if (object->transformedVertices[object->indices[nextIndex]].z >= NCP) continue;   // ������㶼û���ã��Ͳ���¼���ֵ�㣬ֱ������

            tempVertices[j] = approximateVertex(object->transformedVertices[object->indices[i        ]], 
                                                object->transformedVertices[object->indices[nextIndex]]);
            j++;
        }
    }

    if (!haveToBeClipped) return false;
    if (outOfRegionCount == 1) tempVerticesCount = 4;

    return true;
}

void Shader::scanTriangle() {

    bottomOfScan      = SCREENH;// ɨ���ߵײ�
    topOfScan         = 1;      // ɨ���߶���
    
    for (int i = 0; i < tempVerticesCount; i++) {
        pointPosition[i][0] = tempVertices[i].x + H_SCREENW;
        pointPosition[i][1] = tempVertices[i].y + H_SCREENH;
        pointW[i] = 1 / tempVertices[i].z;
    }
    for (int i = 0; i < tempVerticesCount; i++) {
        bottomOfScan      = min(bottomOfScan     , pointPosition[i][1]);
        topOfScan         = max(topOfScan        , pointPosition[i][1]);
    }
    bottomOfScan      = max(bottomOfScan     , 1          );
    topOfScan         = min(topOfScan        , SCREENH - 1);

    bool leftInView = false, rightInView = false;
    for (int i = 0; i < tempVerticesCount; i++) {
        int nextIndex = i + 1;
        if (nextIndex > tempVerticesCount - 1) nextIndex = 0;
        
        int*   p1 = pointPosition[i        ];
        int*   p2 = pointPosition[nextIndex];
        float* w1 = &pointW[i        ];
        float* w2 = &pointW[nextIndex];

        bool startWard = true;  // �ж��ǲ���ɨ���߿�ʼ�ı�
        if (p1[1] > p2[1]) {    // ��֤p1����p2
            startWard = false;
            int* temp = p1;
            p1 = p2;
            p2 = temp;

            float* tempW = w1;
            w1 = w2;
            w2 = tempW;
        }

        float dw = *w2 - *w1;
        int dy = p2[1] - p1[1];
        int dx = p2[0] - p1[0];

        if (dy == 0) continue;  // ɨ����dy == 0 ������

        float gradient = static_cast<float>(dx) / static_cast<float>(dy);
        float gradientW = dw / static_cast<float>(dy); // w��ֱ�ݶ�

        float x = p1[0];
        float w = *w1;
        for (int y = p1[1]; y <= p2[1]; y++, x += gradient, w += gradientW) {   // ¼��ɨ����
            if (y < 1 ) {   // ��ֹ�ڴ����
                int step = 1 - y - 1;
                x += step * gradient;
                w += step * gradientW;
                y += step;
                continue;
            }
            else if (y > SCREENH - 1) break;

            leftInView = x >= 1;
            rightInView = x <= SCREENW - 1;
            if (startWard) {
                xStart[y] = x;
                wStart[y] = w;
            }
            else {
                xEnd[y] = x;
                wEnd[y] = w;
            }
        }
    }

    if (leftInView || rightInView) {
        for (int y = bottomOfScan; y <= topOfScan; y++) {
            if (xStart[y] < 1) {
                float gradientW_x;
                float dw = wEnd[y] - wStart[y];
                int dx = xEnd[y] - xStart[y];
                gradientW_x = dw / static_cast<float>(dx);
                int skip = 1 - xStart[y];
                xStart[y] = 1;
                wStart[y] += skip * gradientW_x;
            }
            if (xEnd[y] > SCREENW - 1) {
                float gradientW_x;
                float dw = wEnd[y] - wStart[y];
                int dx = xEnd[y] - xStart[y];
                gradientW_x = dw / static_cast<float>(dx);
                int skip = xEnd[y] - (SCREENW - 1);
                xEnd[y] = SCREENW - 1;
                wEnd[y] -= skip * gradientW_x;
            }
        }
    }
    // ����ƽ��w�ݶ�
    int middlePosition = (bottomOfScan + topOfScan) / 2;
    int dx = xEnd[middlePosition] - xStart[middlePosition];
    float dw = wEnd[middlePosition] - wStart[middlePosition];
    if (dx == 0) gradientOfW = 0;   // ��ֹ��0ʹ�ݶ�Ϊ����
    else gradientOfW = dw / static_cast<float>(dx);
}

void Shader::rendering(int index) {

    COLORREF currentColor = object->color;
    currentColor = blendColor(currentColor, *light, index);

    for (int y = bottomOfScan; y <= topOfScan; y++) {
        float w = wStart[y];
        for (int x = xStart[y]; x <= xEnd[y]; x++, w += gradientOfW) {
            float z = 1 / w;
            if (z < zBuffer[y * SCREENW + x]) {
                putPixel(x, y, currentColor);
                zBuffer[y * SCREENW + x] = z;
            }
        }
    }
}

COLORREF Shader::blendColor(const COLORREF& currentColor, const ParallelLight& light, const int& index) {

    float H1, S1, V1;
    RGBtoHSV(currentColor, &H1, &S1, &V1);

    float x1 = S1 * LookupTable::SIN(H1);
    float y1 = S1 * LookupTable::COS(H1);

    float H2, S2, V2;
    RGBtoHSV(light.color, &H2, &S2, &V2);

    float x2 = S2 * LookupTable::SIN(H2);
    float y2 = S2 * LookupTable::COS(H2);

    float weight = -object->faceNormals[index / 3].dotCos(light.direction) * 0.5 + 0.5;
    weight *= V2;

    float dx = x2 - x1;
    float dy = y2 - y1;
    float dV = V2 - V1;

    x1 += weight * dx;
    y1 += weight * dy;
    V1 += weight * dV;

    H1 = std::atan(x1 / y1);
    S1 = std::pow(x1 * x1 + y1 * y1, 0.5);

    return HSVtoRGB(H1, S1, V1);
}

void Shader::prepare() {
    
    for (int i = 0; i < SCREEN_SIZE; i++) zBuffer[i] = FCP;
}

void Shader::run() {

    for (Object* o : objects) {

        this->object = o;
        if (renderingType == 1) {
            localRotate();
            translation();
            culculateFaceNormals();
            cameraTransform();
            renderingFace(0, object->numIndices);
        }
    }
}

void Shader::renderingFace(int startIndex, int endIndex) {

    for (int i = startIndex; i < endIndex; i += 3) {

        if (testHidden(i)) {
            continue;
        }
        if (!clipNearPlane(i)) {
            setlinecolor(0x888888);
        }
        else {
            setlinecolor(BLACK);
        }

        perspectiveTransform();
        scanTriangle();
        rendering(i);
        //drawWireFrame();
    }
}

void Shader::putPixel(int x, int y, COLORREF color) {
    int newY = SCREENH - y;                 // ��Ϊֱ�Ӹ���������ֵ������y���ǵ��ŵģ�Ҫ��newY�޸Ĺ���
    pMem[newY * SCREENW + x] = BGR(color);  // ֱ�Ӷ���ʾ��������ֵ
}

COLORREF Shader::getPixel(int x, int y) {
    int newY = SCREENH - y;
    return pMem[newY * SCREENW + x];
}