#include "Object.h"
Object::Object(Mesh _mesh, float _scalar) {

    vertices = _mesh.vertices;
    normals = _mesh.normals;
    uvCoordinates = _mesh.uvCoordinates;
    indices = _mesh.indices;

    numVertices = _mesh.numVertices;
    numNormals = _mesh.numNormals;
    numIndices = _mesh.numIndices;
    numUVs = _mesh.numUVs;

    transformedVertices = new Vector[numVertices];
    faceNormals = new Vector[_mesh.numIndices / 3];
    name = L"";

    position = Vector(0.0, 0.0, 0.0);
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;

    scalar = _scalar;

    color = WHITE;

    for (int i = 0; i < _mesh.numVertices; i++) {

        _mesh.vertices[i] *= scalar;
    }
    float maxX, minX, maxY, minY, maxZ, minZ;
    maxX = _mesh.vertices[0].x;
    minX = _mesh.vertices[0].x;
    maxY = _mesh.vertices[0].y;
    minY = _mesh.vertices[0].y;
    maxZ = _mesh.vertices[0].z;
    minZ = _mesh.vertices[0].z;
    for (int i = 0; i < _mesh.numVertices; i++) {

        maxX = max(_mesh.vertices[i].x, maxX);
        minX = min(_mesh.vertices[i].x, minX);
        maxY = max(_mesh.vertices[i].y, maxY);
        minY = min(_mesh.vertices[i].y, minY);
        maxZ = max(_mesh.vertices[i].z, maxZ);
        minZ = min(_mesh.vertices[i].z, minZ);
    }
    cubeFrame = { Vector(minX, maxY, minZ),
                  Vector(maxX, maxY, minZ),
                  Vector(maxX, maxY, maxZ),
                  Vector(minX, maxY, maxZ),
                  Vector(minX, minY, minZ),
                  Vector(maxX, minY, minZ),
                  Vector(maxX, minY, maxZ),
                  Vector(minX, minY, maxZ) };
}

void Object::setPosition(Vector _position) {

    position = _position;
}

void Object::setAngle(float _xAngle, float _yAngle, float _zAngle) {

    xAngle = _xAngle;
    yAngle = _yAngle;
    zAngle = _zAngle;
}

void Object::setColor(COLORREF _color) {
    color = _color;
}

void Object::setName(std::wstring _name) {
    name = _name;
}

void Object::moveFor(float x, float y, float z) {

    position.x += x;
    position.y += y;
    position.z += z;
}
void Object::rotateFor(float x, float y, float z) {

    xAngle += x;
    yAngle += y;
    zAngle += z;
}

void Object::rotateTo(float x, float y, float z) {

    xAngle = x;
    yAngle = y;
    zAngle = z;
}

Object::~Object() {

    delete[] transformedVertices;
}