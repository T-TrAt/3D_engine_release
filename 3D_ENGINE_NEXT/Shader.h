#pragma once
#include "Global.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include <thread>
#include <vector>
class Shader {
public:
    static std::vector<Object*> objects;                    // 渲染模型存储器
    static DWORD*               pMem;                       // 绘图缓冲区指针

    static float                NCP;                        // 近裁切平面的位置
    static float                FCP;                        // 初始化zBuffer使用的最远距离

    Object*                     object;                     // 渲染的物体
    ParallelLight*              light;                      // 使用的光源

    static float*               zBuffer;                    // 深度值存储
    int                         xStart[SCREENH];            // 扫描线开头 
    int                         xEnd[SCREENH];              // 扫描线结尾
    float                       wStart[SCREENH];            // w扫描线开头 
    float                       wEnd[SCREENH];              // w扫描线结尾
    int                         bottomOfScan;               // 扫描线底部
    int                         topOfScan;                  // 扫描线顶部

    Vector                      tempVertices[4];            // 四个顶底中间量，裁切时使用
    int                         tempVerticesCount = 3;
    int                         pointPosition[4][2];        // 顶点映射到屏幕的二维坐标
    float                       pointW[4];                  // 顶点w值
    float                       gradientOfW;

    int                         threadNumber = 4;           // 允许渲染的线程

    int                         renderingType;              // 渲染模式，正常为0，线框为1

    Shader(int type);                                       // 初始化函数(参数指渲染方式)

    static Vector approximateVertex(Vector p1, Vector p2);  // z裁的线性插值函数

    void localRotate();                     // 局部旋转
    void translation();                     // 平移
    void cameraTransform();                 // 关于相机的平移和旋转
    void culculateFaceNormals();            // 计算面法线
    void perspectiveTransform();            // 投影变换

    void drawWireFrame();                   // 绘制线框

    bool testHidden(int index);             // 隐藏面测试
    bool clipNearPlane(int index);          // 近平面裁切
    void scanTriangle();                    // 转换三角形为扫描线
    void rendering(int index);              // 通过扫描线上色

    COLORREF blendColor(const COLORREF& currentColor, const ParallelLight& light, const int& index);

    void prepare();                         // 渲染前的初始化
    void run();                             // 开始渲染
    void renderingFace(int startIndex, int endIndex);

    static void putPixel(int x, int y, COLORREF color);
    static COLORREF getPixel(int x, int y);
    static void drawLine(int x1, int y1, int x2, int y2, COLORREF color);
};
