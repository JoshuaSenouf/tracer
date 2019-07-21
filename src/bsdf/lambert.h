#ifndef LAMBERT_H
#define LAMBERT_H

#include <string>

#include "bsdf.h"


struct Lambert : public BSDF
{
    Lambert();

    virtual embree::Vec3f Evaluate(PixelSample& pixelSample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
    virtual embree::Vec3fa Sample(PixelSample& pixelSample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
    virtual float Pdf(PixelSample& pixelSample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
};

#endif // LAMBERT_H
