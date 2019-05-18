#include "scenemanager.h"

#include "tbb/parallel_for.h"
#include "tbb/parallel_for_each.h"

#include "trianglemesh.h"
#include "quadmesh.h"


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

    stage = pxr::UsdStage::Open(scenePath);
    device = rtcNewDevice("");
    rootScene = rtcNewScene(device);

    // loadCamera();
    // loadMaterials();
    loadGeometry();

    rtcCommitScene(rootScene);

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
    std::vector<pxr::UsdPrim> primMeshVec;

    getPrimFromType("Mesh", stage, pxr::SdfPath("/"), primMeshVec);

    // tbb::parallel_for_each(primMeshVec.begin(), primMeshVec.end(), [&](pxr::UsdPrim& primMesh)
    for(const pxr::UsdPrim& primMesh: primMeshVec)
    {
        const pxr::TfToken primName = primMesh.GetName();
        const pxr::SdfPath primPath = primMesh.GetPrimPath();

        pxr::UsdGeomMesh geomMesh = pxr::UsdGeomMesh::Get(stage, primPath);

        pxr::VtArray<pxr::GfVec3f> meshPoints;
        pxr::VtArray<int> meshVertexCounts;
        pxr::VtArray<int> meshVertexIndices;

        geomMesh.GetPointsAttr().Get(&meshPoints);
        geomMesh.GetFaceVertexCountsAttr().Get(&meshVertexCounts);
        geomMesh.GetFaceVertexIndicesAttr().Get(&meshVertexIndices);

        bool isTriangleMesh = (static_cast<float>(meshVertexIndices.size()) /
            static_cast<float>(meshVertexCounts.size()) == 3.0f) ? true : false;
        bool isQuadMesh = (static_cast<float>(meshVertexIndices.size()) /
            static_cast<float>(meshVertexCounts.size()) == 4.0f) ? true : false;
        bool needTriangulate = (!isTriangleMesh && !isQuadMesh) ? true : false;

        if (isTriangleMesh)
        {
            TriangleMesh triangleMesh(primMesh,
                geomMesh,
                meshPoints,
                meshVertexIndices
            );

            triangleMesh.create(device);
            triangleMesh.instance(device, rootScene);

            sceneGeom.push_back(triangleMesh);
        }
        else if (isQuadMesh)
        {
            QuadMesh quadMesh(primMesh,
                geomMesh,
                meshPoints,
                meshVertexIndices
            );

            quadMesh.create(device);
            quadMesh.instance(device, rootScene);

            sceneGeom.push_back(quadMesh);
        }
        else if (needTriangulate)
        {
            // pxr::VtArray<int> meshHoleIndices;
            // pxr::TfToken meshOrientation;
            // geomMesh.GetHoleIndicesAttr().Get(&meshHoleIndices);
            // geomMesh.GetOrientationAttr().Get(&meshOrientation);

            // pxr::VtVec3iArray meshTriangulatedIndices = triangulateMeshIndices(meshVertexCounts,
            //     meshVertexIndices,
            //     meshHoleIndices,
            //     meshOrientation);
            
            // TODO
        }
        else
        {
            // TODO
        }

        // meshMutex.lock();
        std::cout << "===================" << std::endl;
        std::cout << "PRIM NAME: " << primName << std::endl;
        std::cout << "PRIM PATH: " << primPath << std::endl;
        std::cout << "ISTRIANGLEMESH: " << isTriangleMesh << std::endl;
        std::cout << "ISQUADMESH: " << isQuadMesh << std::endl;
        std::cout << "NEEDTRIANGULATE: " << needTriangulate << std::endl;
        // meshMutex.unlock();
    }

    return true;
}

const pxr::UsdStageRefPtr& SceneManager::getStage()
{
    return stage;
}

const RTCDevice& SceneManager::getDevice()
{
    return device;
}

const RTCScene& SceneManager::getRootScene()
{
    return rootScene;
}
