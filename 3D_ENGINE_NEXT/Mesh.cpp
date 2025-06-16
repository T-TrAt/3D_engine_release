#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"

Mesh::Mesh(const std::string& objFilePath, const std::string& order, int _type) {

    type = _type;
    if (type == 0) haveTexture(objFilePath, order);
    if (type == 1) noTexture(objFilePath, order);
}

void Mesh::haveTexture(const std::string& objFilePath, const std::string& order) {

    numVertices = 0;    // 初始化数量
    numNormals = 0;
    numIndices = 0;
    numUVs = 0;

    std::ifstream objFile(objFilePath); // 打开文件
    if (!objFile.is_open()) {
        std::cerr << "获取当前目录失败。" << std::endl;
        return;
    }

    std::cout << "开始读取......" << std::endl;
    std::string line;   // 四个成员的计数
    while (std::getline(objFile, line)) {

        if (line.rfind("v ", 0) == 0) {
            numVertices++;
        }
        else if (line.find("vn ", 0) == 0) {
            numNormals++;
        }
        else if (line.rfind("f ", 0) == 0) {
            numIndices += 3;
        }
        else if (line.find("vt ", 0) == 0) {
            numUVs++;
        }
    }
    std::cout << "顶点数：" << numVertices << std::endl;
    std::cout << "法量数：" << numNormals << std::endl;
    std::cout << "面数：" << numIndices << std::endl;
    std::cout << "贴图索引数：" << numUVs << std::endl;

    // 依据计数结果分配内存
    vertices = new Vector[numVertices];
    normals = new Vector[numVertices];
    indices = new int[numIndices];
    uvCoordinates = new float* [numIndices];

    // 创建临时数组以辅助调整法线和 UV 索引
    Vector* normalsTemp = new Vector[numNormals];
    float** uvCoordinatesTemp = new float* [numUVs];

    // 再次读取文件
    objFile.clear();
    objFile.seekg(0);

    int vertexIndex = 0;
    int normalIndex = 0;
    int indexIndex = 0;
    int uvIndex = 0;

    while (std::getline(objFile, line)) {
        if (line.rfind("v ", 0) == 0) {
            float x, y, z;
            (void)sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
            vertices[vertexIndex].set(x, y, z);
            vertexIndex++;
        }
        else if (line.rfind("vn ", 0) == 0) {
            float x, y, z;
            (void)sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
            normalsTemp[normalIndex].set(x, y, z);
            normalIndex++;
        }
        else if (line.rfind("vt ", 0) == 0) {
            float u, v;
            (void)sscanf(line.c_str(), "vt %f %f", &u, &v);
            uvCoordinatesTemp[uvIndex] = new float[2] { u, v };
            uvIndex++;
        }
        else if (line.rfind("f ", 0) == 0) {
            int indicesValues[9];   // 存储f的三个顶点分别对应的三个数值
            (void)sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &indicesValues[0], &indicesValues[1], &indicesValues[2],
                &indicesValues[3], &indicesValues[4], &indicesValues[5],
                &indicesValues[6], &indicesValues[7], &indicesValues[8]);

            if (order == "clockwise") {
                for (int i = 0; i < 3; i++) {
                    int vertexIndexValue = indicesValues[i * 3] - 1;    // 数值一为顶点索引
                    int uvIndexValue = indicesValues[i * 3 + 1] - 1;    // 数值二为纹理索引
                    int normalIndexValue = indicesValues[i * 3 + 2] - 1;// 数值三为法线索引
                    normals[vertexIndexValue].set(normalsTemp[normalIndexValue]);   // 法线是以顶点的索引为索引存储值的
                    uvCoordinates[indexIndex] = new float[2];   // 贴图以面顶点为索引存储值
                    uvCoordinates[indexIndex][0] = uvCoordinatesTemp[uvIndexValue][0];
                    uvCoordinates[indexIndex][1] = uvCoordinatesTemp[uvIndexValue][1];
                    indices[indexIndex] = vertexIndexValue;     // 索引区存储的是顶点索引
                    indexIndex++;
                }
            }
            else {
                for (int i = 2; i >= 0; i--) {
                    int vertexIndexValue = indicesValues[i * 3] - 1;
                    int uvIndexValue = indicesValues[i * 3 + 1] - 1;
                    int normalIndexValue = indicesValues[i * 3 + 2] - 1;
                    normals[vertexIndexValue].set(normalsTemp[normalIndexValue]);
                    uvCoordinates[indexIndex] = uvCoordinatesTemp[uvIndexValue];
                    indices[indexIndex] = vertexIndexValue;
                    indexIndex++;
                }
            }
        }
    }
    std::cout << "读取结束" << std::endl;
}
void Mesh::noTexture(const std::string& objFilePath, const std::string& order) {

    numVertices = 0;    // 初始化数量
    numIndices = 0;

    std::ifstream objFile(objFilePath); // 打开文件
    if (!objFile.is_open()) {
        std::cerr << "获取当前目录失败。" << std::endl;
        return;
    }

    std::cout << "开始读取......" << std::endl;
    std::string line;   // 四个成员的计数
    while (std::getline(objFile, line)) {

        if (line.rfind("v ", 0) == 0) {
            numVertices++;
        }
        else if (line.rfind("f ", 0) == 0) {
            numIndices += 3;
        }
    }
    std::cout << "顶点数：" << numVertices << std::endl;
    std::cout << "面数：" << numIndices << std::endl;

    // 依据计数结果分配内存
    vertices = new Vector[numVertices];
    indices = new int[numIndices];

    // 再次读取文件
    objFile.clear();
    objFile.seekg(0);

    int vertexIndex = 0;
    int indexIndex = 0;

    while (std::getline(objFile, line)) {
        if (line.rfind("v ", 0) == 0) {
            float x, y, z;
            (void)sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
            vertices[vertexIndex].set(x, y, z);
            vertexIndex++;
        }
        else if (line.rfind("f ", 0) == 0) {
            int indicesValues[3];   // 存储f的三个顶点分别对应的三个数值
            (void)sscanf(line.c_str(), "f %d// %d// %d//",
                &indicesValues[0], &indicesValues[1], &indicesValues[2]);

            if (order == "clockwise") {
                for (int i = 0; i < 3; i++) {
                    int vertexIndexValue = indicesValues[i] - 1;    // 数值一为顶点索引
                    indices[indexIndex] = vertexIndexValue;     // 索引区存储的是顶点索引
                    indexIndex++;
                }
            }
            else {
                for (int i = 2; i >= 0; i--) {
                    int vertexIndexValue = indicesValues[i] - 1;    // 数值一为顶点索引
                    indices[indexIndex] = vertexIndexValue;     // 索引区存储的是顶点索引
                    indexIndex++;
                }
            }
        }
    }
    std::cout << "读取结束" << std::endl;
}

/*
Mesh::~Mesh() {

    delete[] vertices;
    delete[] normals;
    delete[] indices;
    for (int i = 0; i < sizeof(uvCoordinates); i++) {
        delete[] uvCoordinates[i];
    }
    delete[] uvCoordinates;
}
*/

