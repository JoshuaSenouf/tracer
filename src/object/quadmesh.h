#ifndef QUADMESH_H
#define QUADMESH_H

#include "geometry.h"


struct QuadMesh : public Geometry
{
    QuadMesh();
    QuadMesh(const pxr::UsdPrim& prim,
        const pxr::UsdGeomMesh& usdGeom,
        const pxr::VtArray<pxr::GfVec3f>& points,
        const pxr::VtArray<int>& indices);

    virtual bool CreatePrototype(const RTCDevice& device) override;
    virtual bool UpdatePrototype() override;

    pxr::VtArray<pxr::GfVec3f> _points;
    pxr::VtArray<int> _indices;
};

#endif // QUADMESH_H
