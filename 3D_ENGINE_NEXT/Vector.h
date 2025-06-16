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

    void rotateX(float angle);	// �ֱ���xyz����ת
    void rotateY(float angle);
    void rotateZ(float angle);

    void unit();	// ��λ��
    void set(float& _x, float& _y, float& _z);  // ��ֵ���ڶ�ȡ�ļ���ʱ�������
    void set(float&& _x, float&& _y, float&& _z);
    void set(const Vector& other);

    void add(const Vector& other, float scalar);	// ʸ����
    void sub(const Vector& other, float scalar);	// ʸ����

    Vector cross(const Vector& other);	// ���
    static Vector cross(const Vector& v1, const Vector& v2);

    float dot(const Vector& other);    // ���
    float dotCos(const Vector& other);

    float length() const;	// ��ȡ����
    float sqLength() const;  // ƽ������

    bool operator==(const Vector& other) const;		// �����жϵ�
    bool operator!=(const Vector& other) const;		// �����жϲ���
    Vector operator+(const Vector& other) const;	// ���ؼӷ�
    Vector operator-(const Vector& other) const;	// ���ؼ���
    Vector operator*(float scalar) const;			// ��������
    Vector operator/(float scalar) const;			// �������� (����)

    Vector& operator+=(const Vector& other);	// ���ؼӵ�
    Vector& operator-=(const Vector& other);	// ���ؼ���
    Vector& operator*=(const float& scalar);    // ���س˵�
    Vector& operator/=(const float& scalar);    // ���س���
};
