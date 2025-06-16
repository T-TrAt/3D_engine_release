#include "Vector.h"

void Vector::rotateX(float angle) {	// 分别绕xyz轴逆时针旋转

    float _z = z;
    float _y = y;
    z = _z * LookupTable::COS(angle) - _y * LookupTable::SIN(angle);
    y = _z * LookupTable::SIN(angle) + _y * LookupTable::COS(angle);
}

void Vector::rotateY(float angle) {

    float _z = z;
    float _x = x;
    z = _z * LookupTable::COS(angle) - _x * LookupTable::SIN(angle);
    x = _z * LookupTable::SIN(angle) + _x * LookupTable::COS(angle);
}

void Vector::rotateZ(float angle) {

    float _x = x;
    float _y = y;
    x = _x * LookupTable::COS(angle) - _y * LookupTable::SIN(angle);
    y = _x * LookupTable::SIN(angle) + _y * LookupTable::COS(angle);
}

void Vector::unit() {

    float length = std::pow(x * x + y * y + z * z, 0.5);
    x /= length;
    y /= length;
    z /= length;
}

void Vector::set(float& _x, float& _y, float& _z) {

    x = _x;
    y = _y;
    z = _z;
}

void Vector::set(float&& _x, float&& _y, float&& _z) {

    x = _x;
    y = _y;
    z = _z;
}

void Vector::set(const Vector& other) {

    x = other.x;
    y = other.y;
    z = other.z;
}

void Vector::add(const Vector& other, float scalar) {

    *this += other * scalar;
}

void Vector::sub(const Vector& other, float scalar) {

    *this -= other * scalar;
}

Vector Vector::cross(const Vector& other) {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector Vector::cross(const Vector& v1, const Vector& v2) {
    return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float Vector::dot(const Vector& other) {
    return x * other.x + y * other.y + z * other.z;
}

float Vector::dotCos(const Vector& other) {

    float dot = x * other.x + y * other.y + z * other.z;
    float len1 = this->length();
    float len2 = other.length();
    return dot / len1 / len2;
}

float Vector::length() const {
    return std::pow(x * x + y * y + z * z, 0.5);
}

float Vector::sqLength() const {
    return x * x + y * y + z * z;
}

bool Vector::operator==(const Vector& other) const {			// 重载判断相等
    return (x == other.x) && (y == other.y) && (z == other.z);
}
bool Vector::operator!=(const Vector& other) const {			// 重载判断不等
    return !(*this == other);
}
Vector Vector::operator+(const Vector& other) const {			// 重载向量加法
    return Vector(x + other.x, y + other.y, z + other.z);
}
Vector Vector::operator-(const Vector& other) const {			// 重载向量减法
    return Vector(x - other.x, y - other.y, z - other.z);
}
Vector Vector::operator*(float scalar) const {					// 重载向量数乘
    return Vector(x * scalar, y * scalar, z * scalar);
}
Vector Vector::operator/(float scalar) const {					// 重载向量数乘 (除法)
    return Vector(x / scalar, y / scalar, z / scalar);
}

Vector& Vector::operator+=(const Vector& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vector& Vector::operator*=(const float& scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Vector& Vector::operator/=(const float& scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}