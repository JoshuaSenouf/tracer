#include "scenemanager.h"

#include "trianglemesh.h"
#include "quadmesh.h"
#include "tbb_helper.h"


SceneManager::SceneManager()
{
}

SceneManager::SceneManager(const std::string& scenePath)
{
    loadScene(scenePath);
}

bool SceneManager::isSceneValid(const std::string& scenePath)
{
    return ((std::size_t(scenePath.rfind(std::string(".usd")) != std::string::npos) ||
        std::size_t(scenePath.rfind(std::string(".usda")) != std::string::npos) ||
        std::size_t(scenePath.rfind(std::string(".usdc")) != std::string::npos) ||
        std::size_t(scenePath.rfind(std::string(".usdz")) != std::string::npos)) ? true : false);
}

bool SceneManager::loadScene(const std::string& scenePath)
{
    if (!isSceneValid(scenePath))
    {
        std::cerr << "ERROR - The following file is not an USD scene: " << scenePath << std::endl;

        return false;
    }

    _stage = pxr::UsdStage::Open(scenePath);
    _device = rtcNewDevice("");
    _scene = rtcNewScene(_device);

    // loadCamera();
    // loadMaterials();
    loadGeometry();

    rtcCommitScene(_scene);

    return true;
}

bool SceneManager::loadGeometry()
{
    loadMeshGeometry();
    // loadCurveGeometry();
    // loadPrimitiveGeometry();

    return true;
}

bool SceneManager::loadMeshGeometry()
{
    std::vector<pxr::UsdPrim> meshPrims;

    getPrimFromType("Mesh", _stage, pxr::SdfPath("/"), meshPrims);

    // for(const pxr::UsdPrim& prim: meshPrims)
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
            triangleMesh->create(_device, _scene);

            _sceneMutex.lock();
            _sceneGeom[triangleMesh.get()->_geomInstanceID] = triangleMesh;
            _sceneMutex.unlock();
        }
        else if (isQuadMesh)
        {
            std::shared_ptr<QuadMesh> quadMesh(std::make_shared<QuadMesh>(prim,
                usdGeom,
                points,
                indices));
            quadMesh->create(_device, _scene);

            _sceneMutex.lock();
            _sceneGeom[quadMesh.get()->_geomInstanceID] = quadMesh;
            _sceneMutex.unlock();
        }
        else if (needTriangulate)
        {
            // pxr::VtArray<int> meshHoleIndices;
            // pxr::TfToken meshOrientation;
            // usdGeom.GetHoleIndicesAttr().Get(&meshHoleIndices);
            // usdGeom.GetOrientationAttr().Get(&meshOrientation);

            // pxr::VtVec3iArray meshTriangulatedIndices(triangulateMeshIndices(indicesCounts,
            //     indices,
            //     meshHoleIndices,
            //     meshOrientation));
            
            // TODO
        }
        else
        {
            // TODO
        }

        // _sceneMutex.lock();
        // std::cout << "===================" << std::endl;
        // std::cout << "PRIM NAME: " << primName << std::endl;
        // std::cout << "PRIM PATH: " << primPath << std::endl;
        // std::cout << "ISTRIANGLEMESH: " << isTriangleMesh << std::endl;
        // std::cout << "ISQUADMESH: " << isQuadMesh << std::endl;
        // std::cout << "NEEDTRIANGULATE: " << needTriangulate << std::endl;
        // _sceneMutex.unlock();
    });
    // }

    return true;
}
