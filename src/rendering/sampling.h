#ifndef SAMPLING_H
#define SAMPLING_H

#include "vector.h"
#include "math_helper.h"


inline Vector3 computeCosineWeightedImportanceSampling(const Vector3& localW,
                                                       const Vector3& localU,
                                                       const Vector3& localV,
                                                       float rand1,
                                                       float rand2,
                                                       float cosT)
{
    return (localU * std::cos(rand1) * rand2 + localV * std::sin(rand1) * rand2 + localW * cosT).normalize();

}


inline Vector3 computePerfectlyReflectedRay(const Vector3& rayDirection, const Vector3& intersectionNormal)
{
    return rayDirection - (intersectionNormal * 2.0f) * intersectionNormal.dot(rayDirection);
}


inline void computeDiffuseMaterial(Vector3& nextRayDir, Vector3& hitCoord, Vector3 hitOrientedNormal, float rand1, float rand2, float cosT)
{
    Vector3 localOrthoW = hitOrientedNormal;
    Vector3 localOrthoU = ((fabs(localOrthoW.x) > 0.1f ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f, 0.0f, 0.0f)).cross(localOrthoW)).normalize();
    Vector3 localOrthoV = localOrthoW.cross(localOrthoU);

    // Cosine Weighted Importance Sampling
    nextRayDir = computeCosineWeightedImportanceSampling(localOrthoW, localOrthoU, localOrthoV, rand1, rand2, cosT);
    hitCoord += hitOrientedNormal * EPSILON;
}


inline void computePerfectSpecularMaterial(Vector3& nextRayDir, Vector3& hitCoord, Vector3 rayDir, Vector3 hitNormal, Vector3 hitOrientedNormal)
{
    nextRayDir = computePerfectlyReflectedRay(rayDir, hitNormal);
    hitCoord += hitOrientedNormal * EPSILON;
}


inline void computePhongMetalMaterial(Vector3& nextRayDir, Vector3& hitCoord, Vector3 rayDir, Vector3 hitNormal, float rand1, float sinT, float cosT)
{
    Vector3 localOrthoW = (rayDir - hitNormal * 2.0f * hitNormal.dot(rayDir)).normalize();
    Vector3 localOrthoU = ((fabs(localOrthoW.x) > 0.1f ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(1.0f, 0.0f, 0.0f)).cross(localOrthoW)).normalize();
    Vector3 localOrthoV = localOrthoW.cross(localOrthoU);

    nextRayDir = computeCosineWeightedImportanceSampling(localOrthoW, localOrthoU, localOrthoV, rand1, sinT, cosT);
    hitCoord += localOrthoW * EPSILON;
}


#endif // SAMPLING_H
