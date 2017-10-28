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
    return (rayDirection - 2.0f) * intersectionNormal * intersectionNormal.dot(rayDirection);
}


#endif // SAMPLING_H
