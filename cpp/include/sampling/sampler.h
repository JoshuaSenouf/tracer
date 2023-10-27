#ifndef SAMPLER_H
#define SAMPLER_H

#include <algorithm>
#include <random>

#include "pcg_random.hpp"

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>


class Sampler
{
    public:
        Sampler();

        pcg_extras::seed_seq_from<std::random_device> NewSeed();
        float Uniform1D();
        embree::Vec2f Uniform2D();
        std::vector<embree::Vec2f> Stratified2D(
            int samples);
        embree::Vec3f HemisphereUniform(
            float rand0,
            float rand1);
        embree::Vec3f HemisphereCosineWeighted(
            float rand0,
            float rand1);
        embree::Vec3f SphereUniform(
            float rand0,
            float rand1);

    private:
        std::uniform_real_distribution<float> float_uniform_distribution;
        pcg32 prng;
};

#endif // SAMPLER_H
