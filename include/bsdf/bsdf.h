#ifndef BSDF_H
#define BSDF_H

#include <string>

#include <embree3/common/math/vec3.h>

#include "render_helper.h"


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
