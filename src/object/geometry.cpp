#include "geometry.h"


Geometry::Geometry()
{
    spdlog::trace("Geometry::Geometry()");
}

bool Geometry::Create(const RTCDevice& device,
    const RTCScene& topScene)
{
    pxr::VtArray<pxr::GfVec3f> displayColor;
    _usdGeom.GetDisplayColorAttr().Get(&displayColor);

    _primName = _prim.GetName();
    // TODO: Get the display color from the correct time value.
    _displayColor = (displayColor.empty() ? embree::Vec3f(0.5f) :
        embree::Vec3f(displayColor[0][0],
            displayColor[0][1],
            displayColor[0][2]));

    CreatePrototype(device);
    CommitPrototype();
    CreateInstance(device, topScene);
    CommitInstance();

    return true;
}

bool Geometry::CreatePrototype(const RTCDevice& device)
{        
    return true;
}

bool Geometry::CreateInstance(const RTCDevice& device,
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

bool Geometry::Commit()
{    
    if (CommitPrototype() && CommitInstance())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Geometry::CommitPrototype()
{
    rtcCommitGeometry(_geom);
    rtcReleaseGeometry(_geom);

    rtcCommitScene(_scene);

    return true;
}

bool Geometry::CommitInstance()
{
    rtcCommitGeometry(_geomInstance);
    rtcReleaseGeometry(_geomInstance);

    return true;
}

bool Geometry::Update()
{
    if (UpdatePrototype() && UpdateInstance())
    {
        if (Commit())
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

bool Geometry::UpdatePrototype()
{    
    return true;
}

bool Geometry::UpdateInstance()
{
    pxr::GfMatrix4d usdTransform(_usdGeomXformCache.GetLocalToWorldTransform(_prim));
    _transform = pxr::GfMatrix4f(usdTransform);

    rtcSetGeometryTransform(_geomInstance,
        0,
        RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
        _transform.GetArray());

    return true;
}

bool Geometry::Clean()
{
    return true;
}