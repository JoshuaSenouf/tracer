#include "usdscene.h"


USDScene::USDScene()
{

}


int USDScene::loadSceneFile(const std::string& scenePath)
{
    sceneStage = pxr::UsdStage::Open(scenePath);
    embreeScene = rtcNewScene(embreeDevice);

    loadMeshes();

    rtcCommitScene(embreeScene);

    return true;
}

void USDScene::loadMeshes()
{
    std::vector<pxr::UsdPrim> usdMeshesVec;

    getPrimFromType("Mesh", pxr::SdfPath("/"), usdMeshesVec);

    for(const pxr::UsdPrim& usdMesh: usdMeshesVec)
        {
            std::cout << "==========\nPRIM NAME: " << usdMesh.GetName() << std::endl;

            pxr::VtArray<pxr::GfVec3f> usdPoints;
            pxr::VtArray<int> usdIndices;

            usdMesh.GetAttribute(pxr::TfToken("points")).Get(&usdPoints);
            usdMesh.GetAttribute(pxr::TfToken("faceVertexIndices")).Get(&usdIndices);

            std::cout << "POINTS SIZE: " << usdPoints.size() << std::endl;
            std::cout << "INDICES SIZE: " << usdIndices.size() << std::endl;

//            for(const pxr::UsdAttribute& usdAttr : usdMesh.GetAttributes())
//            {
//                pxr::VtArray<pxr::GfVec3f> usdPoints;
//                pxr::VtArray<int> usdIndices;

//                if (usdAttr.GetName() == std::string("points"))
//                {
//                    usdAttr.Get(&usdPoints);
//                    std::cout << "OK POINTS!" << std::endl;
//                    std::cout << "POINTS SIZE: " << usdPoints.size() << std::endl;
//                }

//                if (usdAttr.GetName() == std::string("faceVertexIndices"))
//                {
//                    usdAttr.Get(&usdIndices);
//                    std::cout << "OK INDICES!" << std::endl;
//                    std::cout << "INDICES SIZE: " << usdIndices.size() << std::endl;
//                }
//            }
        }
}

void USDScene::getPrimFromType(const std::string& primType,
    const pxr::SdfPath& primPath,
    std::vector<pxr::UsdPrim>& primVector)
{
    pxr::UsdPrim basePrim;
    basePrim = sceneStage->GetPrimAtPath(primPath);

    for(const pxr::UsdPrim& prim: basePrim.GetChildren())
    {
        if (prim.GetTypeName() == primType)
        {
            primVector.push_back(prim);
        }

        if (prim.GetChildren())
        {
            getPrimFromType(primType, prim.GetPath(), primVector);

        }
    }
}
