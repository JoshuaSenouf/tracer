#include <spdlog/spdlog.h>

#include "object/trianglemesh.h"


TriangleMesh::TriangleMesh()
{
    spdlog::trace("TriangleMesh::TriangleMesh()");
}

TriangleMesh::TriangleMesh(
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

bool TriangleMesh::CreatePrototype(
    const RTCDevice &device)
{
    scene = rtcNewScene(device);
    geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
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
        RTC_FORMAT_UINT3,
        indices.cdata(),
        0,
        sizeof(int) * 3,
        indices.size() / 3);

    return true;
}

bool TriangleMesh::UpdatePrototype()
{
    pxr::VtArray<pxr::GfVec3f> points;
    pxr::VtArray<int> indices;
    pxr::VtArray<int> indices_counts;

    usd_geom.GetPointsAttr().Get(&points);
    usd_geom.GetFaceVertexIndicesAttr().Get(&indices);
    usd_geom.GetFaceVertexCountsAttr().Get(&indices_counts);

    bool is_triangle_mesh(
        (static_cast<float>(indices.size()) / static_cast<float>(indices_counts.size()) == 3.0f) ? true : false);

    if (is_triangle_mesh)
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
    else
    {
        // TODO: Triangulation.
    }

    return true;
}
