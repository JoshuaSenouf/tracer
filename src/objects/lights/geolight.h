#ifndef GEOLIGHT_H
#define GEOLIGHT_H

#include "vector.h"
#include "sphere.h"
#include "material.h"


class GeoLight
{
    public:
        GeoLight();
        GeoLight(const std::string& tempName,
            const Sphere& tempGeometry,
            const BSDF& tempMaterial);

        std::string& getName();
        Sphere& getGeometry();
        BSDF& getMaterial();

        void setName(const std::string& tempName);
        void setGeometry(const Sphere& tempGeometry);
        void setMaterial(const BSDF& tempMaterial);

    private:
        std::string name;
        Sphere geometry;
        BSDF material;
};

#endif // GEOLIGHT_H
