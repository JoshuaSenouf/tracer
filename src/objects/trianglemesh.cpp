#include "trianglemesh.h"


TriangleMesh::TriangleMesh(const pxr::UsdPrim& prim,
    const pxr::UsdGeomMesh& usdGeom,
    const pxr::VtArray<pxr::GfVec3f>& points,
    const pxr::VtArray<int>& indices)
{
    _prim = prim;
    _usdGeom = usdGeom;
    _points = points;
    _indices = indices;
}

bool TriangleMesh::create(const RTCDevice& device)
{
    _scene = rtcNewScene(device);
    _geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
    _geomID = rtcAttachGeometry(_scene, _geom);

    rtcSetSharedGeometryBuffer(_geom,
        RTC_BUFFER_TYPE_VERTEX,
        0,
        RTC_FORMAT_FLOAT3,
        _points.cdata(),
        0,
        sizeof(pxr::GfVec3f),
        _points.size());
    rtcSetSharedGeometryBuffer(_geom,
        RTC_BUFFER_TYPE_INDEX,
        0,
        RTC_FORMAT_UINT3,
        _indices.cdata(),
        0,
        sizeof(int) * 3,
        _indices.size() / 3);

    rtcCommitGeometry(_geom);
    rtcReleaseGeometry(_geom);

    rtcCommitScene(_scene);

    return true;
}
