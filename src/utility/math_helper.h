#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#define M_2PI 6.28318530717958647692f
#define M_1_180 0.005555555555555555556f

#include <math.h>

#include <embree3/common/math/vec3.h>

#include <pxr/base/gf/vec3f.h>


inline float DegToRad(float degAngle)
{
    return degAngle * (M_PI / 180.0f);
}

inline float RadToDeg(float radAngle)
{
    return radAngle * (180.0f / M_PI);
}

inline pxr::GfVec3f EmbreeSIMDToUSD(const embree::Vec3fa& embreeVector)
{
    return pxr::GfVec3f(embreeVector.x,
        embreeVector.y,
        embreeVector.z);
}

inline pxr::GfVec3f EmbreeToUSD(const embree::Vec3f& embreeVector)
{
    return pxr::GfVec3f(embreeVector.x,
        embreeVector.y,
        embreeVector.z);
}

inline embree::Vec3f USDToEmbree(const pxr::GfVec3f& usdVector)
{
    return embree::Vec3f(usdVector[0],
        usdVector[1],
        usdVector[2]);
}

inline embree::Vec3fa USDToEmbreeSIMD(const pxr::GfVec3f& usdVector)
{
    return embree::Vec3fa(usdVector[0],
        usdVector[1],
        usdVector[2]);
}

template<typename T, typename A>
A USDToEmbreeMatrixMultiply(const A& embreeVector, const T& usdMatrix)
{
    return A(embreeVector.x * usdMatrix[0][0] +
            embreeVector.y * usdMatrix[1][0] +
            embreeVector.z * usdMatrix[2][0],
        embreeVector.x * usdMatrix[0][1] +
            embreeVector.y * usdMatrix[1][1] +
            embreeVector.z * usdMatrix[2][1],
        embreeVector.x * usdMatrix[0][2] +
            embreeVector.y * usdMatrix[1][2] +
            embreeVector.z * usdMatrix[2][2]);
}

template<typename T, typename A>
A USDToUSDMatrixMultiply(const A& usdVector, const T& usdMatrix)
{
    return A(usdMatrix.TransformDir(usdVector));
}

#endif // MATH_HELPER_H
