#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "randomizer.h"


class BSDF
{
    public:
        BSDF();

        void materialSetup();

        const Vector3 computeSampling(Vector3& rayDirection,
            const Vector3& hitNormal,
            Randomizer& randEngine);
        const Vector3 hemisphereSampling(const Vector3& rayDirection,
            Randomizer& randEngine);
        const Vector3 coneSampling(const Vector3& rayDirection,
            float factor,
            Randomizer& randEngine);
        const Vector3 sphereRandomSampling(float theta,
            float phi);

        const Vector3 computeSchlick(const Vector3& rayDirection,
            const Vector3& hitNormal);
        const Vector3 computeReflectedRay(const Vector3& rayDirection,
            const Vector3& hitNormal);

        std::string& getName();
        Vector3& getColor();
        Vector3& getEmissiveColor();
        Vector3& getFresnelColor();
        float& getRoughness();
        float& getMetalness();
        float& getTransmittance();
        float& getIOR();
        float& getFresnelR0();

        void setName(const std::string& tempName);
        void setColor(const Vector3& tempColor);
        void setEmissiveColor(const Vector3& tempEmissiveColor);
        void setFresnelColor(const Vector3& tempFresnelColor);
        void setRoughness(float tempRoughness);
        void setMetalness(float tempMetalness);
        void setTransmittance(float tempTransmittance);
        void setIOR(float tempIOR);
        void setFresnelR0(float tempFresnelR0);

    private:
        std::string name;
        Vector3 color;
        Vector3 emissiveColor;
        Vector3 fresnelColor;
        float roughness;
        float metalness;
        float transmittance;
        float IOR;
        float fresnelR0;
};


#endif // MATERIAL_H
