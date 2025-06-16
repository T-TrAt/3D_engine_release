#pragma once
#include <easyx.h>
#include "Mesh.h"
struct CubeFrame {
    Vector vertices[8]; // 按下标顺序依次为：上1234，下1234
};
class Object {
public:
    Vector* vertices;           // 顶点
    Vector* normals;            // 法线
    float** uvCoordinates;      // 纹理坐标
    int*    indices;            // 顶点索引
    int     numVertices;        // 顶点数
    int     numNormals;         // 法线数
    int     numIndices;         // 索引数
    int     numUVs;             // 纹理坐标数
    CubeFrame cubeFrame;        // 模型外围的线框，可以作为碰撞箱，暂时不参与旋转运动

    Vector* transformedVertices;

    Vector* faceNormals;        // 存储面法线，用于计算光照
    std::wstring name;          // 名字

    Vector  position;
    float   xAngle;
    float   yAngle;
    float   zAngle;

    float scalar;

    COLORREF color;

    Object(Mesh _mesh, float _scalar);
    void setPosition(Vector _position);
    void setAngle(float _xAngle, float _yAngle, float _zAngle);
    void setColor(COLORREF _color);
    void setName(std::wstring _name);

    void moveFor(float x, float y, float z);
    void moveTo();

    void rotateFor(float x, float y, float z);
    void rotateTo(float x, float y, float z);
    ~Object();
};
