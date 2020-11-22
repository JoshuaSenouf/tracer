// #include "math/vector.h"


// Vector3::Vector3(): x(0.0f),
//     y(0.0f),
//     z(0.0f)
// {
// }

// Vector3::Vector3(
//     float temp_xyz)
// {
//     x = temp_xyz;
//     y = temp_xyz;
//     z = temp_xyz;
// }

// Vector3::Vector3(
//     float temp_x,
//     float temp_y,
//     float temp_z)
// {
//     x = temp_x;
//     y = temp_y;
//     z = temp_z;
// }

// Vector3::Vector3(
//     const pxr::GfVec3f &usd_vec3f)
// {
//     x = usd_vec3f[0];
//     y = usd_vec3f[1];
//     z = usd_vec3f[2];
// }

// float Vector3::Length() const
// {
//     return embree::sqrt(x * x + y * y + z * z);
// }

// Vector3 Vector3::Normalize() const
// {
//     float vec_length = Length();

//     return Vector3(
//         x / vec_length,
//         y / vec_length,
//         z / vec_length);
// }

// float Vector3::Dot(
//     const Vector3 &temp_vec3) const
// {
//     return (x * temp_vec3.x + y * temp_vec3.y + z * temp_vec3.z);
// }

// Vector3 Vector3::Cross(
//     const Vector3 &temp_vec3) const
// {
//     return Vector3(
//         y * temp_vec3.z - z * temp_vec3.y,
//         z * temp_vec3.x - x * temp_vec3.z,
//         x * temp_vec3.y - y * temp_vec3.x);
// }

// Vector3 Vector3::Lerp(
//     const Vector3 &temp_vec3,
//     float weight)
// {
//     return Vector3((*this) + (temp_vec3 - (*this)) * weight);
// }

// void Vector3::Print()
// {
//     std::cout << "X: " << x << "\nY: " << y << "\nZ: " << z << std::endl;
// }

// Vector3 &Vector3::operator+=(
//     const Vector3 &temp_vec3)
// {
//     x += temp_vec3.x;
//     y += temp_vec3.y;
//     z += temp_vec3.z;

//     return *this;
// }

// Vector3 &Vector3::operator-=(
//     const Vector3 &temp_vec3)
// {
//     x -= temp_vec3.x;
//     y -= temp_vec3.y;
//     z -= temp_vec3.z;

//     return *this;
// }

// Vector3 &Vector3::operator*=(
//     const Vector3 &temp_vec3)
// {
//     x *= temp_vec3.x;
//     y *= temp_vec3.y;
//     z *= temp_vec3.z;

//     return *this;
// }

// Vector3 &Vector3::operator*=(
//     float factor)
// {
//     x *= factor;
//     y *= factor;
//     z *= factor;

//     return *this;
// }

// Vector3 &Vector3::operator/=(
//     const Vector3 &temp_vec3)
// {
//     x /= temp_vec3.x;
//     y /= temp_vec3.y;
//     z /= temp_vec3.z;

//     return *this;
// }

// Vector3 &Vector3::operator/=(
//     float factor)
// {
//     x /= factor;
//     y /= factor;
//     z /= factor;

//     return *this;
// }

// Vector3 Vector3::operator+(
//     const Vector3 &temp_vec3) const
// {
//     return Vector3(
//         x + temp_vec3.x,
//         y + temp_vec3.y,
//         z + temp_vec3.z);
// }


// Vector3 Vector3::operator+(
//     float factor) const
// {
//     return Vector3(
//         x + factor,
//         y + factor,
//         z + factor);
// }

// Vector3 Vector3::operator-(
//     const Vector3 &temp_vec3) const
// {
//     return Vector3(
//         x - temp_vec3.x,
//         y - temp_vec3.y,
//         z - temp_vec3.z);
// }

// Vector3 Vector3::operator-(
//     float factor) const
// {
//     return Vector3(
//         x - factor,
//         y - factor,
//         z - factor);
// }

// Vector3 Vector3::operator-() const
// {
//     return Vector3(
//         -(x),
//         -(y),
//         -(z));
// }

// Vector3 Vector3::operator*(
//     const Vector3 &temp_vec3) const
// {
//     return Vector3(
//         x * temp_vec3.x,
//         y * temp_vec3.y,
//         z * temp_vec3.z);
// }

// Vector3 Vector3::operator*(
//     float factor) const
// {
//     return Vector3(
//         x * factor,
//         y * factor,
//         z * factor);
// }

// Vector3 Vector3::operator/(
//     const Vector3 &temp_vec3) const
// {
//     return Vector3(
//         x / temp_vec3.x,
//         y / temp_vec3.y,
//         z / temp_vec3.z);
// }

// Vector3 Vector3::operator/(
//     float factor) const
// {
//     return (*this * (1.0f / factor));
// }

// bool Vector3::operator==(
//     const Vector3 &temp_vec3) const
// {
//     return (x == temp_vec3.x && y == temp_vec3.y && z == temp_vec3.z);
// }

// bool Vector3::operator!=(
//     const Vector3 &temp_vec3) const
// {
//     return !(*this == temp_vec3);
// }

// bool Vector3::operator<(
//     const Vector3 &temp_vec3) const
// {
//     return (x < temp_vec3.x && y < temp_vec3.y && z < temp_vec3.z);
// }

// /////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////

// Vector2::Vector2(): x(0.0f),
//     y(0.0f)
// {
// }

// Vector2::Vector2(
//     float temp_xy)
// {
//     x = temp_xy;
//     y = temp_xy;
// }

// Vector2::Vector2(
//     float temp_x,
//     float temp_y)
// {
//     x = temp_x;
//     y = temp_y;
// }

// Vector2::Vector2(
//     const pxr::GfVec2f &usd_vec2f)
// {
//     x = usd_vec2f[0];
//     y = usd_vec2f[1];
// }

// float Vector2::Length() const
// {
//     return embree::sqrt(x * x + y * y);
// }

// Vector2 Vector2::Normalize() const
// {
//     float vec_length = Length();

//     return Vector2(
//         x / vec_length,
//         y / vec_length);
// }

// float Vector2::Dot(
//     const Vector2 &temp_vec2) const
// {
//     return (x * temp_vec2.x + y * temp_vec2.y);
// }

// void Vector2::Print()
// {
//     std::cout << "X: " << x << "\nY: " << y << std::endl;
// }

// Vector2 &Vector2::operator+=(
//     const Vector2 &temp_vec2)
// {
//     x += temp_vec2.x;
//     y += temp_vec2.y;

//     return *this;
// }

// Vector2 &Vector2::operator-=(
//     const Vector2 &temp_vec2)
// {
//     x -= temp_vec2.x;
//     y -= temp_vec2.y;

//     return *this;
// }

// Vector2 &Vector2::operator*=(
//     const Vector2 &temp_vec2)
// {
//     x *= temp_vec2.x;
//     y *= temp_vec2.y;

//     return *this;
// }

// Vector2 &Vector2::operator*=(
//     float factor)
// {
//     x *= factor;
//     y *= factor;

//     return *this;
// }

// Vector2 &Vector2::operator/=(
//     const Vector2 &temp_vec2)
// {
//     x /= temp_vec2.x;
//     y /= temp_vec2.y;

//     return *this;
// }

// Vector2 &Vector2::operator/=(
//     float factor)
// {
//     x /= factor;
//     y /= factor;

//     return *this;
// }

// Vector2 Vector2::operator+(
//     const Vector2 &temp_vec2) const
// {
//     return Vector2(
//         x + temp_vec2.x,
//         y + temp_vec2.y);
// }

// Vector2 Vector2::operator+(
//     float factor) const
// {
//     return Vector2(
//         x + factor,
//         y + factor);
// }

// Vector2 Vector2::operator-(
//     const Vector2 &temp_vec2) const
// {
//     return Vector2(
//         x - temp_vec2.x,
//         y - temp_vec2.y);
// }

// Vector2 Vector2::operator-(
//     float factor) const
// {
//     return Vector2(
//         x - factor,
//         y - factor);
// }

// Vector2 Vector2::operator-() const
// {
//     return Vector2(
//         -(x),
//         -(y));
// }

// Vector2 Vector2::operator*(
//     const Vector2 &temp_vec2) const
// {
//     return Vector2(
//         x * temp_vec2.x,
//         y * temp_vec2.y);
// }

// Vector2 Vector2::operator*(
//     float factor) const
// {
//     return Vector2(
//         x * factor,
//         y * factor);
// }

// Vector2 Vector2::operator/(
//     const Vector2 &temp_vec2) const
// {
//     return Vector2(
//         x / temp_vec2.x,
//         y / temp_vec2.y);
// }

// Vector2 Vector2::operator/(
//     float factor) const
// {
//     return (*this * (1.0f / factor));
// }

// bool Vector2::operator==(
//     const Vector2 &temp_vec2) const
// {
//     return (x == temp_vec2.x && y == temp_vec2.y);
// }

// bool Vector2::operator!=(
//     const Vector2 &temp_vec2) const
// {
//     return !(*this == temp_vec2);
// }

// /////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////

// std::ostream& operator<<(
//     std::ostream &stream,
//     const Vector3 &temp_vec3)
// {
//     stream << temp_vec3.x << " " << temp_vec3.y << " " << temp_vec3.z;

//     return stream;
// }

// std::ostream& operator<<(
//     std::ostream &stream,
//     const Vector2 &temp_vec2)
// {
//     stream << temp_vec2.x << " " << temp_vec2.y;

//     return stream;
// }
