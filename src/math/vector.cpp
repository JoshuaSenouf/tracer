// #include "vector.h"


// Vector3::Vector3(): x(0.0f),
//     y(0.0f),
//     z(0.0f)
// {
// }

// Vector3::Vector3(float tempXYZ)
// {
//     this->x = tempXYZ;
//     this->y = tempXYZ;
//     this->z = tempXYZ;
// }

// Vector3::Vector3(float tempX, float tempY, float tempZ)
// {
//     this->x = tempX;
//     this->y = tempY;
//     this->z = tempZ;
// }

// Vector3::Vector3(const pxr::GfVec3f &usdVec3f)
// {
//     this->x = usdVec3f[0];
//     this->y = usdVec3f[1];
//     this->z = usdVec3f[2];
// }

// float Vector3::Length() const
// {
//     return embree::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
// }

// Vector3 Vector3::Normalize() const
// {
//     float vecLength = Length();

//     return Vector3(this->x / vecLength,
//         this->y / vecLength,
//         this->z / vecLength);
// }

// float Vector3::Dot(const Vector3 &tempVec3) const
// {
//     return (this->x * tempVec3.x + this->y * tempVec3.y + this->z * tempVec3.z);
// }

// Vector3 Vector3::Cross(const Vector3 &tempVec3) const
// {
//     return Vector3(this->y * tempVec3.z - this->z * tempVec3.y,
//         this->z * tempVec3.x - this->x * tempVec3.z,
//         this->x * tempVec3.y - this->y * tempVec3.x);
// }

// Vector3 Vector3::Lerp(const Vector3& tempVec3, float weightFactor)
// {
//     return Vector3((*this) + (tempVec3 - (*this)) * weightFactor);
// }

// void Vector3::Print()
// {
//     std::cout << "X: " << this->x << "\nY: " << this->y << "\nZ: " << this->z << std::endl;
// }

// Vector3& Vector3::operator+=(const Vector3 &tempVec3)
// {
//     this->x += tempVec3.x;
//     this->y += tempVec3.y;
//     this->z += tempVec3.z;

//     return *this;
// }

// Vector3& Vector3::operator-=(const Vector3 &tempVec3)
// {
//     this->x -= tempVec3.x;
//     this->y -= tempVec3.y;
//     this->z -= tempVec3.z;

//     return *this;
// }

// Vector3& Vector3::operator*=(const Vector3 &tempVec3)
// {
//     this->x *= tempVec3.x;
//     this->y *= tempVec3.y;
//     this->z *= tempVec3.z;

//     return *this;
// }

// Vector3& Vector3::operator*=(float multFactor)
// {
//     this->x *= multFactor;
//     this->y *= multFactor;
//     this->z *= multFactor;

//     return *this;
// }

// Vector3& Vector3::operator/=(const Vector3 &tempVec3)
// {
//     this->x /= tempVec3.x;
//     this->y /= tempVec3.y;
//     this->z /= tempVec3.z;

//     return *this;
// }

// Vector3& Vector3::operator/=(float divFactor)
// {
//     this->x /= divFactor;
//     this->y /= divFactor;
//     this->z /= divFactor;

//     return *this;
// }

// Vector3 Vector3::operator+(const Vector3 &tempVec3) const
// {
//     return Vector3(this->x + tempVec3.x, this->y + tempVec3.y,  this->z + tempVec3.z);
// }


// Vector3 Vector3::operator+(float addFactor) const
// {
//     return Vector3(this->x + addFactor, this->y + addFactor,  this->z + addFactor);
// }

// Vector3 Vector3::operator-(const Vector3 &tempVec3) const
// {
//     return Vector3(this->x - tempVec3.x, this->y - tempVec3.y,  this->z - tempVec3.z);
// }

// Vector3 Vector3::operator-(float subFactor) const
// {
//     return Vector3(this->x - subFactor, this->y - subFactor,  this->z - subFactor);
// }

// Vector3 Vector3::operator-() const
// {
//     return Vector3(-(this->x), -(this->y), -(this->z));
// }

// Vector3 Vector3::operator*(const Vector3 &tempVec3) const
// {
//     return Vector3(this->x * tempVec3.x, this->y * tempVec3.y, this->z * tempVec3.z);
// }

// Vector3 Vector3::operator*(float multFactor) const
// {
//     return Vector3(this->x * multFactor, this->y * multFactor, this->z * multFactor);
// }

// Vector3 Vector3::operator/(const Vector3 &tempVec3) const
// {
//     return Vector3(this->x / tempVec3.x, this->y / tempVec3.y, this->z / tempVec3.z);
// }

// Vector3 Vector3::operator/(float divFactor) const
// {
//     return (*this * (1.0f / divFactor));
// }

// bool Vector3::operator==(const Vector3 &tempVec3) const
// {
//     return (this->x == tempVec3.x && this->y == tempVec3.y && this->z == tempVec3.z);
// }

// bool Vector3::operator!=(const Vector3 &tempVec3) const
// {
//     return !(*this == tempVec3);
// }

// bool Vector3::operator<(const Vector3 &tempVec3) const
// {
//     return (this->x < tempVec3.x && this->y < tempVec3.y && this->z < tempVec3.z);
// }

// /////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////

// Vector2::Vector2(): x(0.0f),
//     y(0.0f)
// {
// }

// Vector2::Vector2(float tempXY)
// {
//     this->x = tempXY;
//     this->y = tempXY;
// }

// Vector2::Vector2(float tempX, float tempY)
// {
//     this->x = tempX;
//     this->y = tempY;
// }

// Vector2::Vector2(const pxr::GfVec2f &usdVec2f)
// {
//     this->x = usdVec2f[0];
//     this->y = usdVec2f[1];
// }

// float Vector2::Length() const
// {
//     return embree::sqrt(this->x * this->x + this->y * this->y);
// }

// Vector2 Vector2::Normalize() const
// {
//     float vecLength = Length();

//     return Vector2(this->x / vecLength, this->y / vecLength);
// }

// float Vector2::Dot(const Vector2 &tempVec2) const
// {
//     return (this->x * tempVec2.x + this->y * tempVec2.y);
// }

// void Vector2::Print()
// {
//     std::cout << "X: " << this->x << "\nY: " << this->y << std::endl;
// }

// Vector2& Vector2::operator+=(const Vector2 &tempVec2)
// {
//     this->x += tempVec2.x;
//     this->y += tempVec2.y;

//     return *this;
// }

// Vector2& Vector2::operator-=(const Vector2 &tempVec2)
// {
//     this->x -= tempVec2.x;
//     this->y -= tempVec2.y;

//     return *this;
// }

// Vector2& Vector2::operator*=(const Vector2 &tempVec2)
// {
//     this->x *= tempVec2.x;
//     this->y *= tempVec2.y;

//     return *this;
// }

// Vector2& Vector2::operator*=(float multFactor)
// {
//     this->x *= multFactor;
//     this->y *= multFactor;

//     return *this;
// }

// Vector2& Vector2::operator/=(const Vector2 &tempVec2)
// {
//     this->x /= tempVec2.x;
//     this->y /= tempVec2.y;

//     return *this;
// }

// Vector2& Vector2::operator/=(float divFactor)
// {
//     this->x /= divFactor;
//     this->y /= divFactor;

//     return *this;
// }

// Vector2 Vector2::operator+(const Vector2 &tempVec2) const
// {
//     return Vector2(this->x + tempVec2.x, this->y + tempVec2.y);
// }

// Vector2 Vector2::operator+(float addFactor) const
// {
//     return Vector2(this->x + addFactor, this->y + addFactor);
// }

// Vector2 Vector2::operator-(const Vector2 &tempVec2) const
// {
//     return Vector2(this->x - tempVec2.x, this->y - tempVec2.y);
// }

// Vector2 Vector2::operator-(float subFactor) const
// {
//     return Vector2(this->x - subFactor, this->y - subFactor);
// }

// Vector2 Vector2::operator-() const
// {
//     return Vector2(-(this->x), -(this->y));
// }

// Vector2 Vector2::operator*(const Vector2 &tempVec2) const
// {
//     return Vector2(this->x * tempVec2.x, this->y * tempVec2.y);
// }

// Vector2 Vector2::operator*(float multFactor) const
// {
//     return Vector2(this->x * multFactor, this->y * multFactor);
// }

// Vector2 Vector2::operator/(const Vector2 &tempVec2) const
// {
//     return Vector2(this->x / tempVec2.x, this->y / tempVec2.y);
// }

// Vector2 Vector2::operator/(float divFactor) const
// {
//     return (*this * (1.0f / divFactor));
// }

// bool Vector2::operator==(const Vector2 &tempVec2) const
// {
//     return (this->x == tempVec2.x && this->y == tempVec2.y);
// }

// bool Vector2::operator!=(const Vector2 &tempVec2) const
// {
//     return !(*this == tempVec2);
// }

// /////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////

// std::ostream& operator<<(std::ostream &os, const Vector3 &tempVec3)
// {
//     os << tempVec3.x << " " << tempVec3.y << " " << tempVec3.z;

//     return os;
// }

// std::ostream& operator<<(std::ostream &os, const Vector2 &tempVec2)
// {
//     os << tempVec2.x << " " << tempVec2.y;

//     return os;
// }
