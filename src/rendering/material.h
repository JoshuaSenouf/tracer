#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "randomizer.h"


class BSDF
{
    public:
        std::string name;
        Vector3 color;
        Vector3 emissiveColor;
        Vector3 fresnelColor;
        float roughness;
        float metalness;
        float transmittance;
        float ior;
        float fresnelR0;

        BSDF();

        void materialSetup();

        const Vector3 computeSampling(Vector3& rayDirection, const Vector3& hitNormal, Randomizer& randEngine);
        const Vector3 hemisphereSampling(const Vector3& rayDirection, Randomizer& randEngine);
        const Vector3 coneSampling(const Vector3& rayDirection, float factor, Randomizer& randEngine);
        const Vector3 sphereRandomSampling(float theta, float phi);

        const Vector3 computeSchlick(const Vector3& rayDirection, const Vector3& hitNormal);
        const Vector3 computeReflectedRay(const Vector3& rayDirection, const Vector3& hitNormal);

    private:

};


#endif // MATERIAL_H
