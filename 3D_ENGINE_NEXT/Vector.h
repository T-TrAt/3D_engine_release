#pragma once
#include "LookupTable.h"
class Vector {
public:

    float x;
    float y;
    float z;

    Vector() : x(0.0), y(0.0), z(0.0) {}
    Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector(const Vector& other) : x(other.x), y(other.y), z(other.z) {}

    void rotateX(float angle);	// 分别绕xyz轴旋转
    void rotateY(float angle);
    void rotateZ(float angle);

    void unit();	// 单位化
    void set(float& _x, float& _y, float& _z);  // 赋值，在读取文件的时候很有用
    void set(float&& _x, float&& _y, float&& _z);
    void set(const Vector& other);

    void add(const Vector& other, float scalar);	// 矢量加
    void sub(const Vector& other, float scalar);	// 矢量减

    Vector cross(const Vector& other);	// 叉乘
    static Vector cross(const Vector& v1, const Vector& v2);

    float dot(const Vector& other);    // 点乘
    float dotCos(const Vector& other);

    float length() const;	// 获取长度
    float sqLength() const;  // 平方长度

    bool operator==(const Vector& other) const;		// 重载判断等
    bool operator!=(const Vector& other) const;		// 重载判断不等
    Vector operator+(const Vector& other) const;	// 重载加法
    Vector operator-(const Vector& other) const;	// 重载减法
    Vector operator*(float scalar) const;			// 重载数乘
    Vector operator/(float scalar) const;			// 重载数乘 (除法)

    Vector& operator+=(const Vector& other);	// 重载加等
    Vector& operator-=(const Vector& other);	// 重载减等
    Vector& operator*=(const float& scalar);    // 重载乘等
    Vector& operator/=(const float& scalar);    // 重载除等
};
