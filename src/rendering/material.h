#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "randomizer.h"
#include "math_helper.h"


class BSDF
{
    public:
        std::string name;
        Vector3 color;
        Vector3 emissiveColor;
        Vector3 fresnel;
        float roughness;
        float metalness;
        float transmittance;
        float ior;

        BSDF();
        BSDF(const std::string& tempName,
             const Vector3& tempColor,
             const Vector3& tempEmissive,
             const Vector3& tempFresnel,
             float tempRoughness,
             float tempMetalness,
             float tempTransmittance,
             float tempIOR);

        const Vector3 computeSampling(Vector3& rayDirection, const Vector3& hitNormal, Randomizer& randEngine);
        const Vector3 hemisphereSampling(const Vector3& rayDirection, Randomizer& randEngine);
        const Vector3 sphereRandomSampling(Randomizer& randEngine);
        const Vector3 angleRandomSampling(float theta, float phi);

    private:

};


#endif // MATERIAL_H
