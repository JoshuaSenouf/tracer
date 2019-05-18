#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>

#include "usd_helper.h"
#include "embree_helper.h"


struct Geometry
{
    Geometry();

    virtual bool create(const RTCDevice& device);
    virtual bool instance(const RTCDevice& device,
        const RTCScene& rootScene);
    virtual bool update();
    virtual bool clean();

    unsigned int _geomID = RTC_INVALID_GEOMETRY_ID;
    unsigned int _geomInstanceID = RTC_INVALID_GEOMETRY_ID;
    RTCScene _scene = nullptr;
    RTCGeometry _geom = nullptr;
    RTCGeometry _geomInstance = nullptr;
    pxr::UsdPrim _prim;
    pxr::UsdGeomMesh _usdGeom;
    pxr::UsdGeomXformCache _usdGeomXformCache;
    pxr::GfMatrix4f _transform;
};

#endif // GEOMETRY_H
