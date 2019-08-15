#ifndef ORENNAYAR_H
#define ORENNAYAR_H

#include <string>

#include "bsdf.h"


struct OrenNayar : public BSDF
{
    OrenNayar();

    virtual embree::Vec3f Evaluate(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
    virtual embree::Vec3fa Sample(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;
    virtual float Pdf(PixelSample& sample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) override;

    float _roughness;
};

#endif // ORENNAYAR_H
