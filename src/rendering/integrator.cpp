#include "integrator.h"


PathTracer::PathTracer()
{

}


Vector3 PathTracer::getRadiance(Ray& cameraRay, Scene& renderScene, Randomizer& randEngine, int rayDepth)
{
    Vector3 colorAccumulation;
    Vector3 colorMask(1.0f, 1.0f, 1.0f);

    for (int bounces = 0; bounces < rayDepth; ++bounces)
    {
        float closestSphereDist;
        int closestSphereID = 0;

        if (!renderScene.isIntersected(cameraRay, closestSphereDist, closestSphereID))
            return colorAccumulation += colorMask * Vector3(0.7f, 0.8f, 0.8f); // If we hit no object, we return the sky color

        const Sphere &hitSphere = renderScene.getSpheresList()[closestSphereID];
        Vector3 hitCoord = cameraRay.origin + cameraRay.direction * closestSphereDist;
        Vector3 hitNormal = (hitCoord - hitSphere.position).normalize();
        Vector3 hitOrientedNormal = hitNormal.dot(cameraRay.direction) < 0.0f ? hitNormal : hitNormal * -1.0f;

        colorAccumulation += colorMask * hitSphere.emissiveColor;

        Vector3 nextRayDir;

        // DIFFUSE
        if (hitSphere.materialID == 1)
        {
            float rand1 = 2.0f * M_PI * randEngine.getRandomFloat();
            float rand2 = randEngine.getRandomFloat();
            float rand2Square = std::sqrt(rand2);
            float cosT = std::sqrt(1.0f - rand2);

            computeDiffuseMaterial(nextRayDir, hitCoord, hitOrientedNormal, rand1, rand2Square, cosT);

            colorMask *= nextRayDir.dot(hitOrientedNormal);
            colorMask *= hitSphere.color;
        }

        // (PERFECT) SPECULAR
        else if (hitSphere.materialID == 2)
        {
            computePerfectSpecularMaterial(nextRayDir, hitCoord, cameraRay.direction, hitNormal, hitOrientedNormal);

            colorMask *= hitSphere.color;
        }

        // REFRACT
        else if (hitSphere.materialID == 3)
        {

        }

        // METAL (PHONG)
        else if (hitSphere.materialID == 4)
        {
            float rand1 = 2.0f * M_PI * randEngine.getRandomFloat();
            float rand2 = randEngine.getRandomFloat();
            float cosTMetal = std::pow(1.0f - rand2, 1.0f / (METAL_EXPO + 1.0f));
            float sinTMetal = std::sqrt(1.0f - cosTMetal * cosTMetal);

            computePhongMetalMaterial(nextRayDir, hitCoord, cameraRay.direction, hitNormal, rand1, sinTMetal, cosTMetal);

            colorMask *= hitSphere.color;
        }

        // GLOSSY/COAT (from Peter Kurtz path tracer, not physically accurate but nice to have anyway)
        else if (hitSphere.materialID == 5)
        {
            float rand1 = randEngine.getRandomFloat();
            bool materialSpecular = (rand1 < GLOSSY_LEVEL);

            // We simply choose between computing a perfect specular or a diffuse material depending of the random value when compared to a certain threshold of glossiness
            if (materialSpecular)
            {
                computePerfectSpecularMaterial(nextRayDir, hitCoord, cameraRay.direction, hitNormal, hitOrientedNormal);

                colorMask *= hitSphere.color;
            }

            else
            {
                float rand1 = 2.0f * M_PI * randEngine.getRandomFloat();
                float rand2 = randEngine.getRandomFloat();
                float rand2Square = std::sqrt(rand2);
                float cosT = std::sqrt(1.0f - rand2);

                computeDiffuseMaterial(nextRayDir, hitCoord, hitOrientedNormal, rand1, rand2Square, cosT);

                colorMask *= nextRayDir.dot(hitOrientedNormal);
                colorMask *= hitSphere.color;
            }
        }

//        colorMask *= LIGHT_INTENSITY;

        cameraRay.direction = nextRayDir;
        cameraRay.origin = hitCoord;
    }

    return colorAccumulation;
}
