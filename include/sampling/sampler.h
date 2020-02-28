#ifndef SAMPLER_H
#define SAMPLER_H

#include <algorithm>
#include <random>

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>


struct Sampler
{
    Sampler();

    unsigned NewSeed();
    float Uniform1D();
    embree::Vec2f Uniform2D();
    std::vector<embree::Vec2f> Stratified2D(int samples);
    embree::Vec3f HemisphereUniform(float rand0, float rand1);
    embree::Vec3f HemisphereCosineWeighted(float rand0, float rand1);
    embree::Vec3f SphereUniform(float rand0, float rand1);

    std::uniform_real_distribution<float> floatUniformDistribution;
    std::mt19937 prng;
};

#endif // SAMPLER_H
