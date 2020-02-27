#include <spdlog/spdlog.h>

#include "quadmesh.h"


QuadMesh::QuadMesh()
{
    spdlog::trace("QuadMesh::QuadMesh()");
}

QuadMesh::QuadMesh(const pxr::UsdPrim& prim,
    const pxr::UsdGeomMesh& usdGeom,
    const pxr::VtArray<pxr::GfVec3f>& points,
    const pxr::VtArray<int>& indices)
{
    _prim = prim;
    _usdGeom = usdGeom;
    _points = points;
    _indices = indices;
}

bool QuadMesh::CreatePrototype(const RTCDevice& device)
{
    _scene = rtcNewScene(device);
    _geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_QUAD);
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
        RTC_FORMAT_UINT4,
        _indices.cdata(),
        0,
        sizeof(int) * 4,
        _indices.size() / 4);

    return true;
}

bool QuadMesh::UpdatePrototype()
{
    pxr::VtArray<pxr::GfVec3f> points;
    pxr::VtArray<int> indices;
    pxr::VtArray<int> indicesCounts;

    _usdGeom.GetPointsAttr().Get(&points);
    _usdGeom.GetFaceVertexIndicesAttr().Get(&indices);
    _usdGeom.GetFaceVertexCountsAttr().Get(&indicesCounts);

    bool isQuadMesh((static_cast<float>(indices.size()) /
        static_cast<float>(indicesCounts.size()) == 4.0f) ? true : false);

    if (isQuadMesh)
    {
        if (_points != points)
        {
            _points = points;
            const pxr::GfVec3f* pointsData((pxr::GfVec3f*)rtcGetGeometryBufferData(_geom,
                RTC_BUFFER_TYPE_VERTEX,
                0));

            pointsData = _points.cdata();
        }
        if (_indices != indices)
        {
            _indices = indices;
            const int* indicesData((int*)rtcGetGeometryBufferData(_geom,
                RTC_BUFFER_TYPE_INDEX,
                0));

            indicesData = _indices.cdata();
        }
    }

    return true;
}
