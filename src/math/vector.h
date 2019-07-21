// #ifndef VECTOR_H
// #define VECTOR_H

// #include <iostream>
// #include <cmath>

// #include <pxr/usd/usd/stage.h>
// #include <pxr/usd/usd/prim.h>
// #include <pxr/usd/usd/attribute.h>
// #include <pxr/base/vt/array.h>


// class Vector3
// {
//     public:
//         float x;
//         float y;
//         float z;

//         Vector3();
//         Vector3(float tempXYZ);
//         Vector3(float tempX, float tempY, float tempZ);
//         Vector3(const pxr::GfVec3f& usdVec3f);

//         float Length() const;
//         Vector3 Normalize() const;
//         float Dot(const Vector3 &tempVec3) const;
//         Vector3 Cross(const Vector3 &tempVec3) const;
//         Vector3 Lerp(const Vector3& tempVec3, float weightFactor);
//         void Print();

//         Vector3& operator+=(const Vector3 &tempVec3);
//         Vector3& operator-=(const Vector3 &tempVec3);
//         Vector3& operator*=(const Vector3 &tempVec3);
//         Vector3& operator*=(float multFactor);
//         Vector3& operator/=(const Vector3 &tempVec3);
//         Vector3& operator/=(float divFactor);
//         Vector3 operator+(const Vector3 &tempVec3) const;
//         Vector3 operator+(float addFactor) const;
//         Vector3 operator-(const Vector3 &tempVec3) const;
//         Vector3 operator-(float subFactor) const;
//         Vector3 operator-() const;
//         Vector3 operator*(const Vector3 &tempVec3) const;
//         Vector3 operator*(float multFactor) const;
//         Vector3 operator/(const Vector3 &tempVec3) const;
//         Vector3 operator/(float divFactor) const;
//         bool operator==(const Vector3 &tempVec3) const;
//         bool operator!=(const Vector3 &tempVec3) const;
//         bool operator<(const Vector3 &tempVec3) const;

//     private:

// };


// class Vector2
// {
//     public:
//         float x;
//         float y;

//         Vector2();
//         Vector2(float tempXY);
//         Vector2(float tempX, float tempY);
//         Vector2(const pxr::GfVec2f& usdVec2f);

//         float Length() const;
//         Vector2 Normalize() const;
//         float Dot(const Vector2 &tempVec2) const;
//         void Print();

//         Vector2& operator+=(const Vector2 &tempVec2);
//         Vector2& operator-=(const Vector2 &tempVec2);
//         Vector2& operator*=(const Vector2 &tempVec2);
//         Vector2& operator*=(float multFactor);
//         Vector2& operator/=(const Vector2 &tempVec2);
//         Vector2& operator/=(float divFactor);
//         Vector2 operator+(const Vector2 &tempVec2) const;
//         Vector2 operator+(float addFactor) const;
//         Vector2 operator-(const Vector2 &tempVec2) const;
//         Vector2 operator-(float subFactor) const;
//         Vector2 operator-() const;
//         Vector2 operator*(const Vector2 &tempVec2) const;
//         Vector2 operator*(float multFactor) const;
//         Vector2 operator/(const Vector2 &tempVec2) const;
//         Vector2 operator/(float divFactor) const;
//         bool operator==(const Vector2 &tempVec2) const;
//         bool operator!=(const Vector2 &tempVec2) const;

//     private:

// };

// std::ostream& operator<<(std::ostream &os, const Vector3 &tempVec3);
// std::ostream& operator<<(std::ostream &os, const Vector2 &tempVec2);

// #endif // VECTOR_H
