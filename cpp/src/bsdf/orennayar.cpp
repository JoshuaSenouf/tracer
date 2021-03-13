#include "utility/math.h"

#include "bsdf/orennayar.h"


OrenNayar::OrenNayar()
{
    roughness_ = 0.5f;
}

embree::Vec3f OrenNayar::Evaluate(
    PixelSample &pixel_sample,
    ShadingPoint &shading_point,
    BSDFSample &bsdf_sample)
{
    float rougness_sqrt(roughness_ * roughness_);
    // We setup Oren-Nayar's specific terms.
	float A = 1 - 0.5f * (rougness_sqrt / (rougness_sqrt + 0.57f));
    float B = 0.45f * (rougness_sqrt / (rougness_sqrt + 0.09f));

    // TODO

    // TODO: "NdotL" should not be the same one as from "Sample()", but the actual dot product of the normal and the light direction?
    return embree::Vec3f(0.0f);
}

embree::Vec3fa OrenNayar::Sample(
    PixelSample &pixel_sample,
    ShadingPoint &shading_point,
    BSDFSample &bsdf_sample)
{
    float rand0 = pixel_sample.sampler.Uniform1D();
    float rand1 = pixel_sample.sampler.Uniform1D();
    embree::Vec3fa random_direction(pixel_sample.sampler.HemisphereCosineWeighted(rand0, rand1));

    float r = embree::sqrt(rand0);
    float theta = 2.0f * M_PI * rand1;
    float phi = embree::sqrt(1.0f - rand1);
    float x = r * embree::cos(theta);
    float y = r * embree::sin(theta);

    // We are orienting the random direction along the normal of the shading point,
    // somehow like when using a orthonormal basis.
    embree::Vec3fa u(embree::normalize(embree::cross(shading_point.Nw, random_direction)));
    embree::Vec3fa v(embree::cross(shading_point.Nw, u));

    embree::Vec3fa wi(shading_point.Nw);
    wi *= phi;
    wi += (u * x);
    wi += (v * y);

    bsdf_sample.NdotL = embree::dot(shading_point.Nw, wi);
    bsdf_sample.pdf = Pdf(pixel_sample, shading_point, bsdf_sample);

    // TODO: Using the basis directly does not yield the same result. This should get looked into.
    // return embree::normalize(USDToEmbreeSIMD(EmbreeSIMDToUSD(wi) * shading_point.basis));
    return wi;
}

float OrenNayar::Pdf(
    PixelSample &pixel_sample,
    ShadingPoint &shading_point,
    BSDFSample &bsdf_sample)
{
    return bsdf_sample.NdotL > 0.0f ? bsdf_sample.NdotL / M_PI : 1.0f;
}
