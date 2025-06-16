#ifndef MESH_H
#define MESH_H

#include "Vector.h"
#include <iostream>
#include <string>
#include <fstream>
class Mesh {
public:
    Vector* vertices;           // ����
    Vector* normals;            // ����
    float** uvCoordinates;      // ��������
    int*    indices;            // ��������
    int     numVertices;        // ������
    int     numNormals;         // ������
    int     numIndices;         // ������
    int     numUVs;             // ����������

    int     type;               // �ļ���ʽ��0Ϊ������1Ϊ��������

    Mesh(const std::string& objFilePath, const std::string& order, int _type);
    //~Mesh();

private:
    void haveTexture(const std::string& objFilePath, const std::string& order);
    void noTexture(const std::string& objFilePath, const std::string& order);
};

#endif // !MESH_H
