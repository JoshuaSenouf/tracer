#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"


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

        const Vector3& computeSampling(Vector3 hitNormal, Vector3 rayDirection, float objectDistance);

    private:

};


#endif // MATERIAL_H
