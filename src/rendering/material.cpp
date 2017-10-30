#include "material.h"


BSDF::BSDF()
{

}


BSDF::BSDF(const std::string& tempName,
           const Vector3& tempColor,
           const Vector3& tempEmissive,
           const Vector3& tempFresnel,
           float tempRoughness,
           float tempMetalness,
           float tempTransmittance,
           float tempIOR) :
    name(tempName),
    color(tempColor),
    emissiveColor(tempEmissive),
    fresnel(tempFresnel),
    roughness(tempRoughness),
    metalness(tempMetalness),
    transmittance(tempTransmittance),
    ior(tempIOR)
{

}


const Vector3& BSDF::computeSampling(Vector3 hitNormal, Vector3 rayDirection, float objectDistance)
{


}
