#ifndef QUADMESH_H
#define QUADMESH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>

#include "geometry.h"


struct QuadMesh : public Geometry
{
    QuadMesh(const pxr::UsdPrim& prim,
        const pxr::UsdGeomMesh& usdGeom,
        const pxr::VtArray<pxr::GfVec3f>& points,
        const pxr::VtArray<int>& indices);

    virtual bool create(const RTCDevice& device) override;

    pxr::VtArray<pxr::GfVec3f> _points;
    pxr::VtArray<int> _indices;
};

#endif // QUADMESH_H
