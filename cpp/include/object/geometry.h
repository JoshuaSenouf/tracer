#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>

#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xformCache.h>
#include <pxr/base/gf/matrix4f.h>


struct Geometry
{
    Geometry();

    virtual bool Create(
        const RTCDevice &device,
        const RTCScene &top_scene);
    virtual bool CreatePrototype(
        const RTCDevice &device);
    virtual bool CreateInstance(
        const RTCDevice &device,
        const RTCScene &top_scene);
    virtual bool Commit();
    virtual bool CommitPrototype();
    virtual bool CommitInstance();
    virtual bool Update();
    virtual bool UpdatePrototype();
    virtual bool UpdateInstance();
    virtual bool Clean();

    unsigned int geom_id = RTC_INVALID_GEOMETRY_ID;
    unsigned int geom_instance_id = RTC_INVALID_GEOMETRY_ID;
    RTCScene scene = nullptr;
    RTCGeometry geom = nullptr;
    RTCGeometry geom_instance = nullptr;
    pxr::UsdPrim prim;
    pxr::TfToken prim_name;
    pxr::UsdGeomMesh usd_geom;
    pxr::UsdGeomXformCache usd_geom_xform_cache;

    // TODO: Should be stored as Embree data since we are meant to interact with it at shading time.
    pxr::GfMatrix4f transform;
    embree::Vec3f display_color;
};

#endif // GEOMETRY_H
