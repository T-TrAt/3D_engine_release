#pragma once
#include <easyx.h>
#include "Mesh.h"
struct CubeFrame {
    Vector vertices[8]; // ���±�˳������Ϊ����1234����1234
};
class Object {
public:
    Vector* vertices;           // ����
    Vector* normals;            // ����
    float** uvCoordinates;      // ��������
    int*    indices;            // ��������
    int     numVertices;        // ������
    int     numNormals;         // ������
    int     numIndices;         // ������
    int     numUVs;             // ����������
    CubeFrame cubeFrame;        // ģ����Χ���߿򣬿�����Ϊ��ײ�䣬��ʱ��������ת�˶�

    Vector* transformedVertices;

    Vector* faceNormals;        // �洢�淨�ߣ����ڼ������
    std::wstring name;          // ����

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
