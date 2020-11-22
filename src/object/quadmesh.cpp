#include <spdlog/spdlog.h>

#include "object/quadmesh.h"


QuadMesh::QuadMesh()
{
    spdlog::trace("QuadMesh::QuadMesh()");
}

QuadMesh::QuadMesh(
    const pxr::UsdPrim &prim,
    const pxr::UsdGeomMesh &usd_geom,
    const pxr::VtArray<pxr::GfVec3f> &points,
    const pxr::VtArray<int> &indices)
{
    this->prim = prim;
    this->usd_geom = usd_geom;
    this->points = points;
    this->indices = indices;
}

bool QuadMesh::CreatePrototype(
    const RTCDevice &device)
{
    scene = rtcNewScene(device);
    geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_QUAD);
    geom_id = rtcAttachGeometry(scene, geom);

    rtcSetSharedGeometryBuffer(
        geom,
        RTC_BUFFER_TYPE_VERTEX,
        0,
        RTC_FORMAT_FLOAT3,
        points.cdata(),
        0,
        sizeof(pxr::GfVec3f),
        points.size());
    rtcSetSharedGeometryBuffer(
        geom,
        RTC_BUFFER_TYPE_INDEX,
        0,
        RTC_FORMAT_UINT4,
        indices.cdata(),
        0,
        sizeof(int) * 4,
        indices.size() / 4);

    return true;
}

bool QuadMesh::UpdatePrototype()
{
    pxr::VtArray<pxr::GfVec3f> points;
    pxr::VtArray<int> indices;
    pxr::VtArray<int> indices_counts;

    usd_geom.GetPointsAttr().Get(&points);
    usd_geom.GetFaceVertexIndicesAttr().Get(&indices);
    usd_geom.GetFaceVertexCountsAttr().Get(&indices_counts);

    bool is_quad_mesh(
        (static_cast<float>(indices.size()) / static_cast<float>(indices_counts.size()) == 4.0f) ? true : false);

    if (is_quad_mesh)
    {
        if (this->points != points)
        {
            this->points = points;
            const pxr::GfVec3f* points_data(
                (pxr::GfVec3f*)rtcGetGeometryBufferData(
                    geom,
                    RTC_BUFFER_TYPE_VERTEX,
                    0));

            points_data = this->points.cdata();
        }
        if (this->indices != indices)
        {
            this->indices = indices;
            const int* indices_data(
                (int*)rtcGetGeometryBufferData(
                    geom,
                    RTC_BUFFER_TYPE_INDEX,
                    0));

            indices_data = this->indices.cdata();
        }
    }

    return true;
}
