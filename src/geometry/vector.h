#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>


class Vector3
{
    public:
        float x, y, z;

        Vector3();
        Vector3(float tempX, float tempY, float tempZ);

        float length() const;
        Vector3 normalize() const;
        float dot(const Vector3 &tempVec3) const;
        Vector3 cross(const Vector3 &tempVec3) const;
        void print();

        Vector3& operator+=(const Vector3 &tempVec3);
        Vector3& operator-=(const Vector3 &tempVec3);
        Vector3& operator*=(float multFactor);
        Vector3& operator/=(float divFactor);
        Vector3 operator+(const Vector3 &tempVec3) const;
        Vector3 operator-(const Vector3 &tempVec3) const;
        Vector3 operator-() const;
        Vector3 operator*(const Vector3 &tempVec3) const;
        Vector3 operator*(float multFactor) const;
        Vector3 operator/(const Vector3 &tempVec3) const;
        Vector3 operator/(float divFactor) const;
        bool operator==(const Vector3 &tempVec3) const;
        bool operator!=(const Vector3 &tempVec3) const;
};

#endif // VECTOR_H
