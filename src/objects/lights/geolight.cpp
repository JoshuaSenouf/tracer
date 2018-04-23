#include "geolight.h"


GeoLight::GeoLight()
{

}


GeoLight::GeoLight(const Sphere& tempGeometry,
    const BSDF& tempMaterial):
    geometry(tempGeometry),
    material(tempMaterial)
{

}


Sphere& GeoLight::getGeometry()
{
    return this->geometry;
}


BSDF& GeoLight::getMaterial()
{
    return this->material;
}


void GeoLight::setGeometry(const Sphere& tempGeometry)
{
    this->geometry = tempGeometry;
}


void GeoLight::setMaterial(const BSDF& tempMaterial)
{
    this->material = tempMaterial;
}
