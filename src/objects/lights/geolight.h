#ifndef GEOLIGHT_H
#define GEOLIGHT_H

#include "vector.h"
#include "sphere.h"
#include "material.h"


class GeoLight
{
    public:
        GeoLight();
        GeoLight(const Sphere& tempGeometry,
            const BSDF& tempMaterial);

        Sphere& getGeometry();
        BSDF& getMaterial();

        void setGeometry(const Sphere& tempGeometry);
        void setMaterial(const BSDF& tempMaterial);

    private:
        Sphere geometry;
        BSDF material;
};

#endif // GEOLIGHT_H
