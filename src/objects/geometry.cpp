#include "geometry.h"


Geometry::Geometry()
{

}

bool Geometry::create(const RTCDevice& device)
{
    // TODO
}

bool Geometry::instance(const RTCDevice& device,
    const RTCScene& rootScene)
{
    _geomInstance = rtcNewGeometry (device, RTC_GEOMETRY_TYPE_INSTANCE);
    _geomInstanceID = rtcAttachGeometry(rootScene, _geomInstance);

    rtcSetGeometryInstancedScene(_geomInstance, _scene);
    rtcSetGeometryTimeStepCount(_geomInstance, 1);

    pxr::GfMatrix4d usdTransform = _usdGeomXformCache.GetLocalToWorldTransform(_prim);
    _transform = pxr::GfMatrix4f(usdTransform);

    rtcSetGeometryTransform(_geomInstance,
        0,
        RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
        _transform.GetArray());

    rtcCommitGeometry(_geomInstance);
    rtcReleaseGeometry(_geomInstance);

    return true;
}

bool Geometry::update()
{
    // TODO
}

bool Geometry::clean()
{
    // TODO
}
