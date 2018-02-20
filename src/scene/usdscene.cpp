#include "usdscene.h"


USDScene::USDScene()
{

}


int USDScene::loadSceneFile(const std::string& scenePath)
{
    sceneStage = pxr::UsdStage::Open(scenePath);

    return true;
}

void USDScene::loadMaterials(std::vector<BSDF>& materialsList)
{
    std::vector<pxr::UsdPrim> usdPrimMaterials;

    getPrimFromType("Material", pxr::SdfPath("/world"), usdPrimMaterials);

    for(const pxr::UsdPrim& usdMaterial: usdPrimMaterials)
    {
        BSDF tempMaterial;

        tempMaterial.name = usdMaterial.GetName();

        for(const pxr::UsdAttribute& usdAttr : usdMaterial.GetAttributes())
        {
            pxr::GfVec3f usdVec3f;

            if (usdAttr.GetName() == std::string("color"))
            {
                usdAttr.Get(&usdVec3f);
                tempMaterial.color = Vector3(usdVec3f);
            }
            else if (usdAttr.GetName() == std::string("emissiveColor"))
            {
                usdAttr.Get(&usdVec3f);
                tempMaterial.emissiveColor = Vector3(usdVec3f);
            }
            else if (usdAttr.GetName() == std::string("fresnelColor"))
            {
                usdAttr.Get(&usdVec3f);
                tempMaterial.fresnelColor = Vector3(usdVec3f);
            }
            else if (usdAttr.GetName() == std::string("roughness"))
                usdAttr.Get(&tempMaterial.roughness);

            else if (usdAttr.GetName() == std::string("metalness"))
                usdAttr.Get(&tempMaterial.metalness);

            else if (usdAttr.GetName() == std::string("transmittance"))
                usdAttr.Get(&tempMaterial.transmittance);

            else if (usdAttr.GetName() == std::string("ior"))
                usdAttr.Get(&tempMaterial.ior);
        }

        materialsList.push_back(tempMaterial);
    }
}


void USDScene::loadSpheres(std::vector<Sphere>& spheresList, std::vector<BSDF>& materialsList)
{
    std::vector<pxr::UsdPrim> usdPrimSpheres;

    getPrimFromType("Sphere", pxr::SdfPath("/world"), usdPrimSpheres);

    for(const pxr::UsdPrim& usdSphere: usdPrimSpheres)
    {
        Sphere tempSphere;

        tempSphere.name = usdSphere.GetName();

        for(const pxr::UsdAttribute& usdAttr : usdSphere.GetAttributes())
        {
            pxr::GfVec3f usdVec3f;

            if (usdAttr.GetName() == std::string("radius"))
                usdAttr.Get(&tempSphere.radius);

            else if (usdAttr.GetName() == std::string("position"))
            {
                usdAttr.Get(&usdVec3f);
                tempSphere.position = Vector3(usdVec3f);
            }
            else if (usdAttr.GetName() == std::string("material"))
            {
                std::string tempMaterialName;
                usdAttr.Get(&tempMaterialName);

                for (const BSDF& currentMaterial : materialsList)
                {
                    if (currentMaterial.name == tempMaterialName)
                        tempSphere.material = currentMaterial;
                }
            }
        }

        spheresList.push_back(tempSphere);
    }
}


void USDScene::loadMeshes(std::vector<Mesh>& meshesList, std::vector<BSDF> &materialsList)
{

}


void USDScene::loadCamera(cameraData& sceneCamera)
{
    std::vector<pxr::UsdPrim> usdPrimCamera;

    getPrimFromType("Camera", pxr::SdfPath("/world"), usdPrimCamera);

    for(const pxr::UsdAttribute& usdAttr: usdPrimCamera[0].GetAttributes())
    {
        pxr::GfVec3f usdVec3f;

        if (usdAttr.GetName() == std::string("position"))
        {
            usdAttr.Get(&usdVec3f);
            sceneCamera.position = Vector3(usdVec3f);
        }
        else if (usdAttr.GetName() == std::string("yaw"))
            usdAttr.Get(&sceneCamera.yaw);
        else if (usdAttr.GetName() == std::string("pitch"))
            usdAttr.Get(&sceneCamera.pitch);
        else if (usdAttr.GetName() == std::string("fov"))
            usdAttr.Get(&sceneCamera.fov);
        else if (usdAttr.GetName() == std::string("apertureRadius"))
            usdAttr.Get(&sceneCamera.apertureRadius);
        else if (usdAttr.GetName() == std::string("focalDistance"))
            usdAttr.Get(&sceneCamera.focalDistance);
    }
}


void USDScene::loadSettings(settingsData& sceneSettings)
{
    std::vector<pxr::UsdPrim> usdPrimSettings;

    getPrimFromType("Settings", pxr::SdfPath("/world"), usdPrimSettings);

    for(const pxr::UsdAttribute& usdAttr: usdPrimSettings[0].GetAttributes())
    {
        pxr::GfVec3f usdVec3f;

        if (usdAttr.GetName() == std::string("skyColor"))
        {
            usdAttr.Get(&usdVec3f);
            sceneSettings.skyColor = Vector3(usdVec3f);
        }
    }
}


void USDScene::getPrimFromType(const std::string& primType, const pxr::SdfPath& primPath, std::vector<pxr::UsdPrim>& primVector)
{
    pxr::UsdPrim worldPrim;
    worldPrim = sceneStage->GetPrimAtPath(primPath);

    for(const pxr::UsdPrim& prim: worldPrim.GetChildren())
    {
        if (prim.GetTypeName() == primType)
            primVector.push_back(prim);

        if (prim.GetChildren())
            getPrimFromType(primType, prim.GetPath(), primVector);
    }
}
