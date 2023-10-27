#include <iterator>

#include "sampling/sampler.h"


Sampler::Sampler():
    float_uniform_distribution(0.0f, 1.0f),
    prng(NewSeed())
{
}

pcg_extras::seed_seq_from<std::random_device> Sampler::NewSeed()
{
    return pcg_extras::seed_seq_from<std::random_device>();
}

float Sampler::Uniform1D()
{
    return float_uniform_distribution(prng);
}

embree::Vec2f Sampler::Uniform2D()
{
    return embree::Vec2f(
        Uniform1D(),
        Uniform1D());
}

std::vector<embree::Vec2f> Sampler::Stratified2D(
    int samples)
{
    std::vector<embree::Vec2f> sample_2d;

    sample_2d.resize(samples);

    for (int sample_idx = 0; sample_idx < samples; ++sample_idx)
    {
        sample_2d[sample_idx][0] = (static_cast<float>(sample_idx) + Uniform1D()) / samples;
    }

    std::shuffle(sample_2d.begin(), sample_2d.end(), prng);

    for (int sample_idx = 0; sample_idx < samples; ++sample_idx)
    {
        sample_2d[sample_idx][1] = (static_cast<float>(sample_idx) + Uniform1D()) / samples;
    }

    return sample_2d;
}

embree::Vec3f Sampler::HemisphereUniform(
    float rand0,
    float rand1)
{
    const float r = embree::sqrt(1.0f - rand0 * rand0);
    const float theta = M_2_PI * rand1;

    return embree::Vec3f(
        r * embree::cos(theta),
        rand0,
        r * embree::sin(theta));
}

embree::Vec3f Sampler::HemisphereCosineWeighted(
    float rand0,
    float rand1)
{
    float r = embree::sqrt(rand0);
    float theta = rand1 * M_2_PI;

    return embree::Vec3f(
        r * embree::cos(theta),
        embree::sqrt(std::max(0.0f, 1.0f - rand0)),
        r * embree::sin(theta));
}

embree::Vec3f Sampler::SphereUniform(
    float rand0,
    float rand1)
{
    float theta = rand0 * M_2_PI;
    float phi = std::asin(rand1 * 2.0f - 1.0f);

    return embree::Vec3f(
        embree::cos(theta) * embree::cos(phi),
        embree::sin(phi),
        embree::sin(theta) * embree::cos(phi));
}
