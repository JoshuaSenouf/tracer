#ifndef GEOLIGHT_H
#define GEOLIGHT_H

#include "vector.h"
#include "sphere.h"
#include "material.h"


class GeoLight
{
    public:
        GeoLight();
        GeoLight(const Sphere& tempGeometry);

        Sphere& getGeometry();
        BSDF& getMaterial();

    private:
        Sphere geometry;
};

#endif // GEOLIGHT_H
