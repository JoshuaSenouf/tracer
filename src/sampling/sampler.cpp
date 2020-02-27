#include <iterator>

#include "sampler.h"


Sampler::Sampler():
    floatUniformDistribution(0.0f, 1.0f),
    prng(NewSeed())
{
}

unsigned Sampler::NewSeed()
{
    std::uniform_int_distribution<unsigned> seed;
    std::random_device rng;

    return seed(rng);
}

float Sampler::Uniform1D()
{
    return floatUniformDistribution(prng);
}

embree::Vec2f Sampler::Uniform2D()
{
    return embree::Vec2f(Uniform1D(), Uniform1D());
}

std::vector<embree::Vec2f> Sampler::Stratified2D(int samples)
{
    std::vector<embree::Vec2f> sample2D;

    sample2D.resize(samples);

    for (int sampleIdx = 0; sampleIdx < samples; ++sampleIdx)
    {
        sample2D[sampleIdx][0] = (static_cast<float>(sampleIdx) + Uniform1D()) / samples;
    }

    std::shuffle(sample2D.begin(), sample2D.end(), prng);

    for (int sampleIdx = 0; sampleIdx < samples; ++sampleIdx)
    {
        sample2D[sampleIdx][1] = (static_cast<float>(sampleIdx) + Uniform1D()) / samples;
    }

    return sample2D;
}

embree::Vec3f Sampler::HemisphereUniform(float rand0, float rand1)
{
    const float r = embree::sqrt(1.0f - rand0 * rand0);
    const float theta = M_2_PI * rand1;
 
    return embree::Vec3f(r * embree::cos(theta),
        rand0,
        r * embree::sin(theta));
}

embree::Vec3f Sampler::HemisphereCosineWeighted(float rand0, float rand1)
{
    float r = embree::sqrt(rand0);
    float theta = rand1 * M_2_PI;

    return embree::Vec3f(r * embree::cos(theta),
        embree::sqrt(std::max(0.0f, 1.0f - rand0)),
        r * embree::sin(theta));
}

embree::Vec3f Sampler::SphereUniform(float rand0, float rand1)
{
    float theta = rand0 * M_2_PI;
    float phi = std::asin(rand1 * 2.0f - 1.0f);

    return embree::Vec3f(embree::cos(theta) * embree::cos(phi),
        embree::sin(phi),
        embree::sin(theta) * embree::cos(phi));
}
