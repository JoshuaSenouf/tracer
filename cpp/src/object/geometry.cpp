#include <spdlog/spdlog.h>

#include "object/geometry.h"


Geometry::Geometry()
{
    spdlog::trace("Geometry::Geometry()");
}

bool Geometry::Create(
    const RTCDevice &device,
    const RTCScene &top_scene)
{
    pxr::VtArray<pxr::GfVec3f> display_color;
    usd_geom.GetDisplayColorAttr().Get(&display_color);

    prim_name = prim.GetName();
    // TODO: Get the display color from the correct time value.
    this->display_color = (
        display_color.empty() ? embree::Vec3f(0.5f) :
            embree::Vec3f(
                display_color[0][0],
                display_color[0][1],
                display_color[0][2]));

    CreatePrototype(device);
    CommitPrototype();
    CreateInstance(device, top_scene);
    CommitInstance();

    return true;
}

bool Geometry::CreatePrototype(
    const RTCDevice &device)
{
    return true;
}

bool Geometry::CreateInstance(
    const RTCDevice &device,
    const RTCScene &top_scene)
{
    geom_instance = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_INSTANCE);
    geom_instance_id = rtcAttachGeometry(top_scene, geom_instance);

    rtcSetGeometryInstancedScene(geom_instance, scene);
    rtcSetGeometryTimeStepCount(geom_instance, 1);

    pxr::GfMatrix4d usd_transform(usd_geom_xform_cache.GetLocalToWorldTransform(prim));
    transform = pxr::GfMatrix4f(usd_transform);

    rtcSetGeometryTransform(geom_instance,
        0,
        RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
        transform.GetArray());

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
    rtcCommitGeometry(geom);
    rtcReleaseGeometry(geom);

    rtcCommitScene(scene);

    return true;
}

bool Geometry::CommitInstance()
{
    rtcCommitGeometry(geom_instance);
    rtcReleaseGeometry(geom_instance);

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
    pxr::GfMatrix4d usd_transform(usd_geom_xform_cache.GetLocalToWorldTransform(prim));
    transform = pxr::GfMatrix4f(usd_transform);

    rtcSetGeometryTransform(geom_instance,
        0,
        RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
        transform.GetArray());

    return true;
}

bool Geometry::Clean()
{
    return true;
}
