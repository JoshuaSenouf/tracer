#ifndef BSDF_H
#define BSDF_H

#include <string>

#include "sampler.h"

#include "embree_helper.h"
#include "math_helper.h"
#include "render_helper.h"
#include "usd_helper.h"


struct BSDF
{
    BSDF();

    virtual embree::Vec3f Evaluate(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) = 0;
    virtual embree::Vec3fa Sample(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) = 0;
    virtual float Pdf(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) = 0;

    std::string _name;
};

#endif // BSDF_H
