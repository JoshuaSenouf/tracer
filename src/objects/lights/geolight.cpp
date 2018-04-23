#include "geolight.h"


GeoLight::GeoLight()
{

}


GeoLight::GeoLight(const Sphere& tempGeometry) :
    geometry(tempGeometry)
{

}


Sphere& GeoLight::getGeometry()
{
    return geometry;
}


BSDF& GeoLight::getMaterial()
{
    return geometry.getMaterial();
}