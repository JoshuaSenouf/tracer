#include "geolight.h"


GeoLight::GeoLight()
{

}


GeoLight::GeoLight(const std::string& tempName,
    const Sphere& tempGeometry,
    const BSDF& tempMaterial):
    name(tempName),
    geometry(tempGeometry),
    material(tempMaterial)
{

}


std::string& GeoLight::getName()
{
    return this->name;
}


Sphere& GeoLight::getGeometry()
{
    return this->geometry;
}


BSDF& GeoLight::getMaterial()
{
    return this->material;
}


void GeoLight::setName(const std::string& tempName)
{
    this->name = tempName;
}


void GeoLight::setGeometry(const Sphere& tempGeometry)
{
    this->geometry = tempGeometry;
}


void GeoLight::setMaterial(const BSDF& tempMaterial)
{
    this->material = tempMaterial;
}
