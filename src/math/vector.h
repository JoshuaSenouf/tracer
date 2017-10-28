#ifndef VECTOR_H
#define VECTOR_H

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
        Vector3 operator+(float addFactor) const;
        Vector3 operator-(const Vector3 &tempVec3) const;
        Vector3 operator-(float subFactor) const;
        Vector3 operator-() const;
        Vector3 operator*(const Vector3 &tempVec3) const;
        Vector3 operator*(float multFactor) const;
        Vector3 operator/(const Vector3 &tempVec3) const;
        Vector3 operator/(float divFactor) const;
        bool operator==(const Vector3 &tempVec3) const;
        bool operator!=(const Vector3 &tempVec3) const;
};


class Vector2
{
    public:
        float x, y;

        Vector2();
        Vector2(float tempX, float tempY);

        float length() const;
        Vector2 normalize() const;
        float dot(const Vector2 &tempVec2) const;
        void print();

        Vector2& operator+=(const Vector2 &tempVec2);
        Vector2& operator-=(const Vector2 &tempVec2);
        Vector2& operator*=(float multFactor);
        Vector2& operator/=(float divFactor);
        Vector2 operator+(const Vector2 &tempVec2) const;
        Vector2 operator+(float addFactor) const;
        Vector2 operator-(const Vector2 &tempVec2) const;
        Vector2 operator-(float subFactor) const;
        Vector2 operator-() const;
        Vector2 operator*(const Vector2 &tempVec2) const;
        Vector2 operator*(float multFactor) const;
        Vector2 operator/(const Vector2 &tempVec2) const;
        Vector2 operator/(float divFactor) const;
        bool operator==(const Vector2 &tempVec2) const;
        bool operator!=(const Vector2 &tempVec2) const;
};


std::ostream& operator<<(std::ostream &os, const Vector3 &tempVec3);
std::ostream& operator<<(std::ostream &os, const Vector2 &tempVec2);



#endif // VECTOR_H
