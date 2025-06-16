#pragma once
#include "Global.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include <thread>
#include <vector>
class Shader {
public:
    static std::vector<Object*> objects;                    // ��Ⱦģ�ʹ洢��
    static DWORD*               pMem;                       // ��ͼ������ָ��

    static float                NCP;                        // ������ƽ���λ��
    static float                FCP;                        // ��ʼ��zBufferʹ�õ���Զ����

    Object*                     object;                     // ��Ⱦ������
    ParallelLight*              light;                      // ʹ�õĹ�Դ

    static float*               zBuffer;                    // ���ֵ�洢
    int                         xStart[SCREENH];            // ɨ���߿�ͷ 
    int                         xEnd[SCREENH];              // ɨ���߽�β
    float                       wStart[SCREENH];            // wɨ���߿�ͷ 
    float                       wEnd[SCREENH];              // wɨ���߽�β
    int                         bottomOfScan;               // ɨ���ߵײ�
    int                         topOfScan;                  // ɨ���߶���

    Vector                      tempVertices[4];            // �ĸ������м���������ʱʹ��
    int                         tempVerticesCount = 3;
    int                         pointPosition[4][2];        // ����ӳ�䵽��Ļ�Ķ�ά����
    float                       pointW[4];                  // ����wֵ
    float                       gradientOfW;

    int                         threadNumber = 4;           // ������Ⱦ���߳�

    int                         renderingType;              // ��Ⱦģʽ������Ϊ0���߿�Ϊ1

    Shader(int type);                                       // ��ʼ������(����ָ��Ⱦ��ʽ)

    static Vector approximateVertex(Vector p1, Vector p2);  // z�õ����Բ�ֵ����

    void localRotate();                     // �ֲ���ת
    void translation();                     // ƽ��
    void cameraTransform();                 // ���������ƽ�ƺ���ת
    void culculateFaceNormals();            // �����淨��
    void perspectiveTransform();            // ͶӰ�任

    void drawWireFrame();                   // �����߿�

    bool testHidden(int index);             // ���������
    bool clipNearPlane(int index);          // ��ƽ�����
    void scanTriangle();                    // ת��������Ϊɨ����
    void rendering(int index);              // ͨ��ɨ������ɫ

    COLORREF blendColor(const COLORREF& currentColor, const ParallelLight& light, const int& index);

    void prepare();                         // ��Ⱦǰ�ĳ�ʼ��
    void run();                             // ��ʼ��Ⱦ
    void renderingFace(int startIndex, int endIndex);

    static void putPixel(int x, int y, COLORREF color);
    static COLORREF getPixel(int x, int y);
    static void drawLine(int x1, int y1, int x2, int y2, COLORREF color);
};
