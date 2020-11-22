#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#define M_2PI 6.28318530717958647692f
#define M_1_180 0.005555555555555555556f

#include <math.h>

#include <embree3/common/math/vec3.h>

#include <pxr/base/gf/vec3f.h>


inline float DegToRad(
    float deg_angle)
{
    return deg_angle * (M_PI / 180.0f);
}

inline float RadToDeg(
    float rad_angle)
{
    return rad_angle * (180.0f / M_PI);
}

inline pxr::GfVec3f EmbreeSIMDToUSD(
    const embree::Vec3fa &embree_vec)
{
    return pxr::GfVec3f(
        embree_vec.x,
        embree_vec.y,
        embree_vec.z);
}

inline pxr::GfVec3f EmbreeToUSD(
    const embree::Vec3f &embree_vec)
{
    return pxr::GfVec3f(
        embree_vec.x,
        embree_vec.y,
        embree_vec.z);
}

inline embree::Vec3f USDToEmbree(
    const pxr::GfVec3f &usd_vec)
{
    return embree::Vec3f(
        usd_vec[0],
        usd_vec[1],
        usd_vec[2]);
}

inline embree::Vec3fa USDToEmbreeSIMD(
    const pxr::GfVec3f &usd_vec)
{
    return embree::Vec3fa(
        usd_vec[0],
        usd_vec[1],
        usd_vec[2]);
}

template<typename T, typename A>
A USDToEmbreeMatrixMultiply(
    const A &embree_vec,
    const T &usd_mat)
{
    return A(
        embree_vec.x * usd_mat[0][0] +
            embree_vec.y * usd_mat[1][0] +
            embree_vec.z * usd_mat[2][0],
        embree_vec.x * usd_mat[0][1] +
            embree_vec.y * usd_mat[1][1] +
            embree_vec.z * usd_mat[2][1],
        embree_vec.x * usd_mat[0][2] +
            embree_vec.y * usd_mat[1][2] +
            embree_vec.z * usd_mat[2][2]);
}

template<typename T, typename A>
A USDToUSDMatrixMultiply(
    const A &usd_vec,
    const T &usd_mat)
{
    return A(
        usd_mat.TransformDir(usd_vec));
}

#endif // MATH_HELPER_H
