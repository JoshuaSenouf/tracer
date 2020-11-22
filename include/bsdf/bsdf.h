#ifndef BSDF_H
#define BSDF_H

#include <string>

#include <embree3/common/math/vec3.h>

#include "utility/render_helper.h"


class BSDF
{
    public:
        BSDF();

        virtual embree::Vec3f Evaluate(
            PixelSample &pixel_sample,
            ShadingPoint &shading_point,
            BSDFSample &bsdf_sample) = 0;
        virtual embree::Vec3fa Sample(
            PixelSample &pixel_sample,
            ShadingPoint &shading_point,
            BSDFSample &bsdf_sample) = 0;
        virtual float Pdf(
            PixelSample &pixel_sample,
            ShadingPoint &shading_point,
            BSDFSample &bsdf_sample) = 0;
};

#endif // BSDF_H
