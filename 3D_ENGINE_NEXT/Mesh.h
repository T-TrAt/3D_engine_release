#ifndef MESH_H
#define MESH_H

#include "Vector.h"
#include <iostream>
#include <string>
#include <fstream>
class Mesh {
public:
    Vector* vertices;           // 顶点
    Vector* normals;            // 法线
    float** uvCoordinates;      // 纹理坐标
    int*    indices;            // 顶点索引
    int     numVertices;        // 顶点数
    int     numNormals;         // 法线数
    int     numIndices;         // 索引数
    int     numUVs;             // 纹理坐标数

    int     type;               // 文件格式，0为含纹理，1为不含纹理

    Mesh(const std::string& objFilePath, const std::string& order, int _type);
    //~Mesh();

private:
    void haveTexture(const std::string& objFilePath, const std::string& order);
    void noTexture(const std::string& objFilePath, const std::string& order);
};

#endif // !MESH_H
