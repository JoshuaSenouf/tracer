#include "orennayar.h"


OrenNayar::OrenNayar()
{
    _roughness = 0.5f;
}

embree::Vec3f OrenNayar::Evaluate(PixelSample& sample,
    ShadingPoint& shadingPoint,
    BSDFSample& bsdfSample)
{
    float roughnessSqrt(_roughness * _roughness);
    // We setup Oren-Nayar's specific terms.
	float A = 1 - 0.5f * (roughnessSqrt / (roughnessSqrt + 0.57f));
    float B = 0.45f * (roughnessSqrt / (roughnessSqrt + 0.09f));

    // TODO

    // TODO: "NdotL" should not be the same one as from "Sample()", but the actual dot product of the normal and the light direction?
    return embree::Vec3f(0.0f);
}

embree::Vec3fa OrenNayar::Sample(PixelSample& sample,
    ShadingPoint& shadingPoint,
    BSDFSample& bsdfSample)
{
    float rand0 = sample.sampler.Uniform1D();
    float rand1 = sample.sampler.Uniform1D();
    embree::Vec3fa randomDirection(sample.sampler.HemisphereCosineWeighted(rand0, rand1));

    float r = embree::sqrt(rand0);
    float theta = 2.0f * M_PI * rand1;
    float phi = embree::sqrt(1.0f - rand1);
    float x = r * embree::cos(theta);
    float y = r * embree::sin(theta);

    // We are orienting the random direction along the normal of the shading point,
    // somehow like when using a orthonormal basis.
    embree::Vec3fa u(embree::normalize(embree::cross(shadingPoint.Nw, randomDirection)));
    embree::Vec3fa v(embree::cross(shadingPoint.Nw, u));

    embree::Vec3fa wi(shadingPoint.Nw);
    wi *= phi;
    wi += (u * x);
    wi += (v * y);

    bsdfSample.NdotL = embree::dot(shadingPoint.Nw, wi);
    bsdfSample.pdf = Pdf(sample, shadingPoint, bsdfSample);

    // TODO: Using the basis directly does not yield the same result. This should get looked into.
    // return embree::normalize(USDToEmbreeSIMD(EmbreeSIMDToUSD(wi) * shadingPoint.basis));
    return wi;
}

float OrenNayar::Pdf(PixelSample& sample,
    ShadingPoint& shadingPoint,
    BSDFSample& bsdfSample)
{
    return bsdfSample.NdotL > 0.0f ? bsdfSample.NdotL / M_PI : 1.0f;
}
