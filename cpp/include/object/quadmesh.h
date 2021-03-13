#ifndef QUADMESH_H
#define QUADMESH_H

#include "object/geometry.h"


struct QuadMesh : public Geometry
{
    QuadMesh();
    QuadMesh(
        const pxr::UsdPrim &prim,
        const pxr::UsdGeomMesh &usd_geom,
        const pxr::VtArray<pxr::GfVec3f> &points,
        const pxr::VtArray<int> &indices);

    virtual bool CreatePrototype(
        const RTCDevice &device) override;
    virtual bool UpdatePrototype() override;

    pxr::VtArray<pxr::GfVec3f> points;
    pxr::VtArray<int> indices;
};

#endif // QUADMESH_H
