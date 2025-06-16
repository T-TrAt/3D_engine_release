#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.h"

Mesh::Mesh(const std::string& objFilePath, const std::string& order, int _type) {

    type = _type;
    if (type == 0) haveTexture(objFilePath, order);
    if (type == 1) noTexture(objFilePath, order);
}

void Mesh::haveTexture(const std::string& objFilePath, const std::string& order) {

    numVertices = 0;    // ��ʼ������
    numNormals = 0;
    numIndices = 0;
    numUVs = 0;

    std::ifstream objFile(objFilePath); // ���ļ�
    if (!objFile.is_open()) {
        std::cerr << "��ȡ��ǰĿ¼ʧ�ܡ�" << std::endl;
        return;
    }

    std::cout << "��ʼ��ȡ......" << std::endl;
    std::string line;   // �ĸ���Ա�ļ���
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
    std::cout << "��������" << numVertices << std::endl;
    std::cout << "��������" << numNormals << std::endl;
    std::cout << "������" << numIndices << std::endl;
    std::cout << "��ͼ��������" << numUVs << std::endl;

    // ���ݼ�����������ڴ�
    vertices = new Vector[numVertices];
    normals = new Vector[numVertices];
    indices = new int[numIndices];
    uvCoordinates = new float* [numIndices];

    // ������ʱ�����Ը����������ߺ� UV ����
    Vector* normalsTemp = new Vector[numNormals];
    float** uvCoordinatesTemp = new float* [numUVs];

    // �ٴζ�ȡ�ļ�
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
            int indicesValues[9];   // �洢f����������ֱ��Ӧ��������ֵ
            (void)sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &indicesValues[0], &indicesValues[1], &indicesValues[2],
                &indicesValues[3], &indicesValues[4], &indicesValues[5],
                &indicesValues[6], &indicesValues[7], &indicesValues[8]);

            if (order == "clockwise") {
                for (int i = 0; i < 3; i++) {
                    int vertexIndexValue = indicesValues[i * 3] - 1;    // ��ֵһΪ��������
                    int uvIndexValue = indicesValues[i * 3 + 1] - 1;    // ��ֵ��Ϊ��������
                    int normalIndexValue = indicesValues[i * 3 + 2] - 1;// ��ֵ��Ϊ��������
                    normals[vertexIndexValue].set(normalsTemp[normalIndexValue]);   // �������Զ��������Ϊ�����洢ֵ��
                    uvCoordinates[indexIndex] = new float[2];   // ��ͼ���涥��Ϊ�����洢ֵ
                    uvCoordinates[indexIndex][0] = uvCoordinatesTemp[uvIndexValue][0];
                    uvCoordinates[indexIndex][1] = uvCoordinatesTemp[uvIndexValue][1];
                    indices[indexIndex] = vertexIndexValue;     // �������洢���Ƕ�������
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
    std::cout << "��ȡ����" << std::endl;
}
void Mesh::noTexture(const std::string& objFilePath, const std::string& order) {

    numVertices = 0;    // ��ʼ������
    numIndices = 0;

    std::ifstream objFile(objFilePath); // ���ļ�
    if (!objFile.is_open()) {
        std::cerr << "��ȡ��ǰĿ¼ʧ�ܡ�" << std::endl;
        return;
    }

    std::cout << "��ʼ��ȡ......" << std::endl;
    std::string line;   // �ĸ���Ա�ļ���
    while (std::getline(objFile, line)) {

        if (line.rfind("v ", 0) == 0) {
            numVertices++;
        }
        else if (line.rfind("f ", 0) == 0) {
            numIndices += 3;
        }
    }
    std::cout << "��������" << numVertices << std::endl;
    std::cout << "������" << numIndices << std::endl;

    // ���ݼ�����������ڴ�
    vertices = new Vector[numVertices];
    indices = new int[numIndices];

    // �ٴζ�ȡ�ļ�
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
            int indicesValues[3];   // �洢f����������ֱ��Ӧ��������ֵ
            (void)sscanf(line.c_str(), "f %d// %d// %d//",
                &indicesValues[0], &indicesValues[1], &indicesValues[2]);

            if (order == "clockwise") {
                for (int i = 0; i < 3; i++) {
                    int vertexIndexValue = indicesValues[i] - 1;    // ��ֵһΪ��������
                    indices[indexIndex] = vertexIndexValue;     // �������洢���Ƕ�������
                    indexIndex++;
                }
            }
            else {
                for (int i = 2; i >= 0; i--) {
                    int vertexIndexValue = indicesValues[i] - 1;    // ��ֵһΪ��������
                    indices[indexIndex] = vertexIndexValue;     // �������洢���Ƕ�������
                    indexIndex++;
                }
            }
        }
    }
    std::cout << "��ȡ����" << std::endl;
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

