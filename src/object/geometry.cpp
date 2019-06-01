#include "geometry.h"


Geometry::Geometry()
{

}

bool Geometry::create(const RTCDevice& device,
    const RTCScene& topScene)
{
    pxr::VtArray<pxr::GfVec3f> displayColor;
    _usdGeom.GetDisplayColorAttr().Get(&displayColor);

    // TODO: Get the display color from the correct time value.
    _color = (displayColor.empty() ? embree::Vec3f(0.5f) :
        embree::Vec3f(displayColor[0][0],
            displayColor[0][1],
            displayColor[0][2]));

    createPrototype(device);
    commitPrototype();
    createInstance(device, topScene);
    commitInstance();

    return true;
}

bool Geometry::createPrototype(const RTCDevice& device)
{        
    return true;
}

bool Geometry::createInstance(const RTCDevice& device,
    const RTCScene& topScene)
{
    _geomInstance = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_INSTANCE);
    _geomInstanceID = rtcAttachGeometry(topScene, _geomInstance);

    rtcSetGeometryInstancedScene(_geomInstance, _scene);
    rtcSetGeometryTimeStepCount(_geomInstance, 1);

    pxr::GfMatrix4d usdTransform(_usdGeomXformCache.GetLocalToWorldTransform(_prim));
    _transform = pxr::GfMatrix4f(usdTransform);

    rtcSetGeometryTransform(_geomInstance,
        0,
        RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
        _transform.GetArray());

    return true;
}

bool Geometry::commit()
{    
    if (commitPrototype() && commitInstance())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Geometry::commitPrototype()
{
    rtcCommitGeometry(_geom);
    rtcReleaseGeometry(_geom);

    rtcCommitScene(_scene);

    return true;
}

bool Geometry::commitInstance()
{
    rtcCommitGeometry(_geomInstance);
    rtcReleaseGeometry(_geomInstance);

    return true;
}

bool Geometry::update()
{
    if (updatePrototype() && updateInstance())
    {
        if (commit())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Geometry::updatePrototype()
{    
    return true;
}

bool Geometry::updateInstance()
{
    pxr::GfMatrix4d usdTransform(_usdGeomXformCache.GetLocalToWorldTransform(_prim));
    _transform = pxr::GfMatrix4f(usdTransform);

    rtcSetGeometryTransform(_geomInstance,
        0,
        RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
        _transform.GetArray());

    return true;
}

bool Geometry::clean()
{
    return true;
}