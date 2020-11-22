#include <spdlog/spdlog.h>

#include <tbb/parallel_for_each.h>

#include "object/quadmesh.h"
#include "object/trianglemesh.h"
#include "utility/usd_helper.h"

#include "scene/scenemanager.h"


SceneManager::SceneManager()
{
    spdlog::trace("SceneManager::SceneManager()");
}

SceneManager::SceneManager(
    const std::string &scene_path)
{
    spdlog::trace("SceneManager::SceneManager(scene_path)");

    LoadScene(scene_path);
}

bool SceneManager::IsSceneValid(
    const std::string &scene_path)
{
    spdlog::trace("SceneManager::IsSceneValid()");

    return ((std::size_t(scene_path.rfind(std::string(".usd")) != std::string::npos) ||
        std::size_t(scene_path.rfind(std::string(".usda")) != std::string::npos) ||
        std::size_t(scene_path.rfind(std::string(".usdc")) != std::string::npos) ||
        std::size_t(scene_path.rfind(std::string(".usdz")) != std::string::npos)) ? true : false);
}

bool SceneManager::LoadScene(
    const std::string &scene_path)
{
    spdlog::trace("SceneManager::LoadScene()");

    if (!IsSceneValid(scene_path))
    {
        spdlog::error(
            "SceneManager::Trace() - "
            "The provided input path is not a valid USD scene file: " + scene_path);

        return false;
    }

    spdlog::debug(
        "SceneManager::LoadScene() - "
        "The provided input path is a valid USD scene file.");

    stage = pxr::UsdStage::Open(scene_path);
    device = rtcNewDevice("");
    scene = rtcNewScene(device);

    // LoadCamera();
    // LoadMaterials();
    LoadGeometry();

    rtcCommitScene(scene);

    spdlog::debug(
        "SceneManager::LoadScene() - "
        "USD Scene loaded successfully.");

    return true;
}

bool SceneManager::LoadGeometry()
{
    spdlog::trace("SceneManager::LoadGeometry()");

    LoadMeshGeometry();
    // LoadCurveGeometry();
    // LoadPrimitiveGeometry();

    spdlog::debug(
        "SceneManager::LoadGeometry() - "
        "Loaded USD Geometry data.");

    return true;
}

bool SceneManager::LoadMeshGeometry()
{
    spdlog::trace("SceneManager::LoadMeshGeometry()");

    std::vector<pxr::UsdPrim> mesh_prims;

    GetPrimsFromType("Mesh", stage, pxr::SdfPath("/"), mesh_prims);

    tbb::parallel_for_each(mesh_prims.begin(), mesh_prims.end(), [&](pxr::UsdPrim &prim)
    {
        const pxr::TfToken prim_name(prim.GetName());
        const pxr::SdfPath prim_path(prim.GetPrimPath());

        pxr::UsdGeomMesh usd_geom(pxr::UsdGeomMesh::Get(stage, prim_path));

        pxr::VtArray<pxr::GfVec3f> points;
        pxr::VtArray<int> indices_counts;
        pxr::VtArray<int> indices;

        usd_geom.GetPointsAttr().Get(&points);
        usd_geom.GetFaceVertexIndicesAttr().Get(&indices);
        usd_geom.GetFaceVertexCountsAttr().Get(&indices_counts);

        bool is_triangle_mesh(
            (static_cast<float>(indices.size()) / static_cast<float>(indices_counts.size()) == 3.0f) ? true : false);
        bool is_quad_mesh(
            (static_cast<float>(indices.size()) / static_cast<float>(indices_counts.size()) == 4.0f) ? true : false);
        bool need_triangulate((!is_triangle_mesh && !is_quad_mesh) ? true : false);

        if (is_triangle_mesh)
        {
            std::shared_ptr<TriangleMesh> triangle_mesh(
                std::make_shared<TriangleMesh>(
                    prim,
                    usd_geom,
                    points,
                    indices));
            triangle_mesh->Create(device, scene);

            mutex.lock();
            scene_geom[triangle_mesh->geom_instance_id] = triangle_mesh;
            mutex.unlock();

            spdlog::debug(
                "SceneManager::LoadGeometry() - "
                "Created TriangleMesh Geometry: " + triangle_mesh->prim_name.GetString() + ".");
        }
        else if (is_quad_mesh)
        {
            std::shared_ptr<QuadMesh> quad_mesh(
                std::make_shared<QuadMesh>(
                    prim,
                    usd_geom,
                    points,
                    indices));
            quad_mesh->Create(device, scene);

            mutex.lock();
            scene_geom[quad_mesh->geom_instance_id] = quad_mesh;
            mutex.unlock();

            spdlog::debug(
                "SceneManager::LoadGeometry() - "
                "Created QuadMesh Geometry: " + quad_mesh->prim_name.GetString() + ".");
        }
        else if (need_triangulate)
        {
            // pxr::VtArray<int> mesh_hole_indices;
            // pxr::TfToken mesh_orientation;
            // usd_geom.GetHoleIndicesAttr().Get(&mesh_hole_indices);
            // usd_geom.GetOrientationAttr().Get(&mesh_orientation);

            // pxr::VtVec3iArray mesh_triangulated_indices(
            //     TriangulateMeshIndices(indices_counts,
            //     indices,
            //     mesh_hole_indices,
            //     mesh_orientation));

            // TODO

            spdlog::debug(
                "SceneManager::LoadGeometry() - "
                "Non-conforming Geometry found: " + prim_name.GetString() + ". "
                "Need triangulation. Skipping...");
        }
        else
        {
            // TODO ?
        }
    });

    spdlog::debug(
        "SceneManager::LoadMeshGeometry() - "
        "Loaded USD Mesh Geometry data.");

    return true;
}
