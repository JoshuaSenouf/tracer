#ifndef LAMBERT_H
#define LAMBERT_H

#include "bsdf.h"


struct Lambert : public BSDF
{
    Lambert();

    virtual embree::Vec3f Evaluate(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
    virtual embree::Vec3fa Sample(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
    virtual float Pdf(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
};

#endif // LAMBERT_H
