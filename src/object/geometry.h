#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <spdlog/spdlog.h>

#include "embree_helper.h"
#include "usd_helper.h"


struct Geometry
{
    Geometry();

    virtual bool Create(const RTCDevice& device,
        const RTCScene& topScene);
    virtual bool CreatePrototype(const RTCDevice& device);
    virtual bool CreateInstance(const RTCDevice& device,
        const RTCScene& topScene);
    virtual bool Commit();
    virtual bool CommitPrototype();
    virtual bool CommitInstance();
    virtual bool Update();
    virtual bool UpdatePrototype();
    virtual bool UpdateInstance();
    virtual bool Clean();

    unsigned int _geomID = RTC_INVALID_GEOMETRY_ID;
    unsigned int _geomInstanceID = RTC_INVALID_GEOMETRY_ID;
    
    RTCScene _scene = nullptr;
    RTCGeometry _geom = nullptr;
    RTCGeometry _geomInstance = nullptr;
    pxr::UsdPrim _prim;
    pxr::TfToken _primName;
    pxr::UsdGeomMesh _usdGeom;
    pxr::UsdGeomXformCache _usdGeomXformCache;
    pxr::GfMatrix4f _transform;
    embree::Vec3f _displayColor;
};

#endif // GEOMETRY_H
