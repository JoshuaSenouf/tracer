#include "scenemanager.h"

#include "trianglemesh.h"
#include "quadmesh.h"
#include "tbb_helper.h"


SceneManager::SceneManager()
{
    spdlog::trace("SceneManager::SceneManager()");
}

SceneManager::SceneManager(const std::string& scenePath)
{
    spdlog::trace("SceneManager::SceneManager(scenePath)");

    LoadScene(scenePath);
}

bool SceneManager::IsSceneValid(const std::string& scenePath)
{
    spdlog::trace("SceneManager::IsSceneValid()");

    return ((std::size_t(scenePath.rfind(std::string(".usd")) != std::string::npos) ||
        std::size_t(scenePath.rfind(std::string(".usda")) != std::string::npos) ||
        std::size_t(scenePath.rfind(std::string(".usdc")) != std::string::npos) ||
        std::size_t(scenePath.rfind(std::string(".usdz")) != std::string::npos)) ? true : false);
}

bool SceneManager::LoadScene(const std::string& scenePath)
{
    spdlog::trace("SceneManager::LoadScene()");

    if (!IsSceneValid(scenePath))
    {
        spdlog::error("SceneManager::Trace() - "
            "The provided input path is not a valid USD scene file: " + scenePath);

        return false;
    }

    spdlog::info("SceneManager::LoadScene() - "
        "The provided input path is a valid USD scene file.");

    _stage = pxr::UsdStage::Open(scenePath);
    _device = rtcNewDevice("");
    _scene = rtcNewScene(_device);

    // LoadCamera();
    // LoadMaterials();
    LoadGeometry();

    rtcCommitScene(_scene);

    spdlog::info("SceneManager::LoadScene() - "
        "USD Scene loaded successfully.");

    return true;
}

bool SceneManager::LoadGeometry()
{
    spdlog::trace("SceneManager::LoadGeometry()");

    LoadMeshGeometry();
    // LoadCurveGeometry();
    // LoadPrimitiveGeometry();

    spdlog::debug("SceneManager::LoadGeometry() - "
        "Loaded USD Geometry data.");

    return true;
}

bool SceneManager::LoadMeshGeometry()
{
    spdlog::trace("SceneManager::LoadMeshGeometry()");

    std::vector<pxr::UsdPrim> meshPrims;

    GetPrimFromType("Mesh", _stage, pxr::SdfPath("/"), meshPrims);

    tbb::parallel_for_each(meshPrims.begin(), meshPrims.end(), [&](pxr::UsdPrim& prim)
    {
        const pxr::TfToken primName(prim.GetName());
        const pxr::SdfPath primPath(prim.GetPrimPath());

        pxr::UsdGeomMesh usdGeom(pxr::UsdGeomMesh::Get(_stage, primPath));

        pxr::VtArray<pxr::GfVec3f> points;
        pxr::VtArray<int> indicesCounts;
        pxr::VtArray<int> indices;

        usdGeom.GetPointsAttr().Get(&points);
        usdGeom.GetFaceVertexIndicesAttr().Get(&indices);
        usdGeom.GetFaceVertexCountsAttr().Get(&indicesCounts);

        bool isTriangleMesh((static_cast<float>(indices.size()) /
            static_cast<float>(indicesCounts.size()) == 3.0f) ? true : false);
        bool isQuadMesh((static_cast<float>(indices.size()) /
            static_cast<float>(indicesCounts.size()) == 4.0f) ? true : false);
        bool needTriangulate((!isTriangleMesh && !isQuadMesh) ? true : false);

        if (isTriangleMesh)
        {
            std::shared_ptr<TriangleMesh> triangleMesh(std::make_shared<TriangleMesh>(prim,
                usdGeom,
                points,
                indices));
            triangleMesh->Create(_device, _scene);

            _sceneMutex.lock();
            _sceneGeom[triangleMesh->_geomInstanceID] = triangleMesh;
            _sceneMutex.unlock();

            spdlog::debug("SceneManager::LoadGeometry() - "
                "Created TriangleMesh Geometry: " + triangleMesh->_primName.GetString() + ".");
        }
        else if (isQuadMesh)
        {
            std::shared_ptr<QuadMesh> quadMesh(std::make_shared<QuadMesh>(prim,
                usdGeom,
                points,
                indices));
            quadMesh->Create(_device, _scene);

            _sceneMutex.lock();
            _sceneGeom[quadMesh->_geomInstanceID] = quadMesh;
            _sceneMutex.unlock();

            spdlog::debug("SceneManager::LoadGeometry() - "
                "Created QuadMesh Geometry: " + quadMesh->_primName.GetString() + ".");
        }
        else if (needTriangulate)
        {
            // pxr::VtArray<int> meshHoleIndices;
            // pxr::TfToken meshOrientation;
            // usdGeom.GetHoleIndicesAttr().Get(&meshHoleIndices);
            // usdGeom.GetOrientationAttr().Get(&meshOrientation);

            // pxr::VtVec3iArray meshTriangulatedIndices(TriangulateMeshIndices(indicesCounts,
            //     indices,
            //     meshHoleIndices,
            //     meshOrientation));
            
            // TODO

            spdlog::debug("SceneManager::LoadGeometry() - "
                "Non-conform Geometry found: " + primName.GetString() + ". "
                "Need triangulation. Skipping...");
        }
        else
        {
            // TODO ?
        }
    });

    spdlog::debug("SceneManager::LoadMeshGeometry() - "
        "Loaded USD Mesh Geometry data.");

    return true;
}
