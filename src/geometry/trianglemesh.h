#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>

#include "geometry.h"


struct TriangleMesh : public Geometry
{
    TriangleMesh();
    TriangleMesh(const pxr::UsdPrim& prim,
        const pxr::UsdGeomMesh& usdGeom,
        const pxr::VtArray<pxr::GfVec3f>& points,
        const pxr::VtArray<int>& indices);

    virtual bool createPrototype(const RTCDevice& device) override;
    virtual bool updatePrototype() override;

    pxr::VtArray<pxr::GfVec3f> _points;
    pxr::VtArray<int> _indices;
};

#endif // TRIANGLEMESH_H
