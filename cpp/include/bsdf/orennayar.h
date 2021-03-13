#ifndef ORENNAYAR_H
#define ORENNAYAR_H

#include "bsdf/bsdf.h"


class OrenNayar : public BSDF
{
    public:
        OrenNayar();

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

    private:
        float roughness_;
};

#endif // ORENNAYAR_H
