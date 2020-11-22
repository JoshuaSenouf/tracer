#ifndef LAMBERT_H
#define LAMBERT_H

#include "bsdf/bsdf.h"


class Lambert : public BSDF
{
    public:
        Lambert();

        virtual embree::Vec3f Evaluate(
            PixelSample &pixel_sample,
            ShadingPoint &shading_point,
            BSDFSample &bsdf_sample) override;
        virtual embree::Vec3fa Sample(
            PixelSample &pixel_sample,
            ShadingPoint &shading_point,
            BSDFSample &bsdf_sample) override;
        virtual float Pdf(
            PixelSample &pixel_sample,
            ShadingPoint &shading_point,
            BSDFSample &bsdf_sample) override;
};

#endif // LAMBERT_H
