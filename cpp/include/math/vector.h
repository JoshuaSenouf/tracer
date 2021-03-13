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
//         Vector3(
//             float temp_xyz);
//         Vector3(
//             float temp_x,
//             float temp_y,
//             float temp_z);
//         Vector3(
//             const pxr::GfVec3f &usd_vec3f);

//         float Length() const;
//         Vector3 Normalize() const;
//         float Dot(
//             const Vector3 &temp_vec3) const;
//         Vector3 Cross(
//             const Vector3 &temp_vec3) const;
//         Vector3 Lerp(
//             const Vector3 &temp_vec3,
//             float weight);
//         void Print();

//         Vector3& operator+=(
//             const Vector3 &temp_vec3);
//         Vector3& operator-=(
//             const Vector3 &temp_vec3);
//         Vector3& operator*=(
//             const Vector3 &temp_vec3);
//         Vector3& operator*=(
//             float factor);
//         Vector3& operator/=(
//             const Vector3 &temp_vec3);
//         Vector3& operator/=(
//             float factor);
//         Vector3 operator+(
//             const Vector3 &temp_vec3) const;
//         Vector3 operator+(
//             float factor) const;
//         Vector3 operator-(
//             const Vector3 &temp_vec3) const;
//         Vector3 operator-(
//             float factor) const;
//         Vector3 operator-() const;
//         Vector3 operator*(
//             const Vector3 &temp_vec3) const;
//         Vector3 operator*(
//             float factor) const;
//         Vector3 operator/(
//             const Vector3 &temp_vec3) const;
//         Vector3 operator/(
//             float factor) const;
//         bool operator==(
//             const Vector3 &temp_vec3) const;
//         bool operator!=(
//             const Vector3 &temp_vec3) const;
//         bool operator<(
//             const Vector3 &temp_vec3) const;
// };


// class Vector2
// {
//     public:
//         float x;
//         float y;

//         Vector2();
//         Vector2(
//             float temp_xy);
//         Vector2(
//             float temp_x, float temp_y);
//         Vector2(
//             const pxr::GfVec2f &usd_vec2f);

//         float Length() const;
//         Vector2 Normalize() const;
//         float Dot(
//             const Vector2 &temp_vec2) const;
//         void Print();

//         Vector2& operator+=(
//             const Vector2 &temp_vec2);
//         Vector2& operator-=(
//             const Vector2 &temp_vec2);
//         Vector2& operator*=(
//             const Vector2 &temp_vec2);
//         Vector2& operator*=(
//             float factor);
//         Vector2& operator/=(
//             const Vector2 &temp_vec2);
//         Vector2& operator/=(
//             float factor);
//         Vector2 operator+(
//             const Vector2 &temp_vec2) const;
//         Vector2 operator+(
//             float factor) const;
//         Vector2 operator-(
//             const Vector2 &temp_vec2) const;
//         Vector2 operator-(
//             float factor) const;
//         Vector2 operator-() const;
//         Vector2 operator*(
//             const Vector2 &temp_vec2) const;
//         Vector2 operator*(
//             float factor) const;
//         Vector2 operator/(
//             const Vector2 &temp_vec2) const;
//         Vector2 operator/(
//             float factor) const;
//         bool operator==(
//             const Vector2 &temp_vec2) const;
//         bool operator!=(
//             const Vector2 &temp_vec2) const;
// };

// std::ostream& operator<<(
//     std::ostream &stream,
//     const Vector3 &temp_vec3);
// std::ostream& operator<<(
//     std::ostream &stream,
//     const Vector2 &temp_vec2);

// #endif // VECTOR_H
