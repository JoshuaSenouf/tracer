#include "scenemanager.h"


SceneManager::SceneManager()
{

}


SceneManager::SceneManager(const std::string& scenePath)
{
    loadScene(scenePath);
}


int SceneManager::loadScene(const std::string& scenePath)
{
    cleanScene();

    if (std::size_t(scenePath.rfind(std::string(".xml")) != std::string::npos))
    {
        if (!xmlScene.loadSceneFile(scenePath))
            return false;

        xmlScene.loadMaterials(materialList);
        xmlScene.loadSpheres(sphereList, materialList);
        xmlScene.loadMeshes(meshList, materialList);
        xmlScene.loadCamera(sceneCamera);
        xmlScene.loadSettings(sceneSettings);
    }
    else if (std::size_t(scenePath.rfind(std::string(".usd")) != std::string::npos)
             || std::size_t(scenePath.rfind(std::string(".usda")) != std::string::npos)
             || std::size_t(scenePath.rfind(std::string(".usdc")) != std::string::npos))
    {
        if (!usdScene.loadSceneFile(scenePath))
            return false;

        usdScene.loadMaterials(materialList);
        usdScene.loadSpheres(sphereList, materialList);
        usdScene.loadMeshes(meshList, materialList);
        usdScene.loadCamera(sceneCamera);
        usdScene.loadSettings(sceneSettings);
    }
    else
    {
        std::cout << "ERROR - The following file is neither a XML or an USD scene: " << scenePath << std::endl;
        return false;
    }
}


void SceneManager::printMaterialData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "MATERIALS COUNT : " << materialList.size() << "\n" << std::endl;

    for(unsigned int i = 0; i < materialList.size(); ++i)
    {
        std::cout << "NAME : " << materialList[i].name << std::endl;
        std::cout << "COL X : " << materialList[i].color.x <<
            " COL Y : " << materialList[i].color.y <<
            " COL Z : " << materialList[i].color.z << std::endl;
        std::cout << "EMI X : " << materialList[i].emissiveColor.x <<
            " EMI Y : " << materialList[i].emissiveColor.y <<
            " EMI Z : " << materialList[i].emissiveColor.z << std::endl;
        std::cout << "FRESNEL X : " << materialList[i].fresnelColor.x <<
            " FRESNEL Y : " << materialList[i].fresnelColor.y <<
            " FRESNEL Z : " << materialList[i].fresnelColor.z << std::endl;
        std::cout << "ROUGHNESS : " << materialList[i].roughness << std::endl;
        std::cout << "METALNESS : " << materialList[i].metalness << std::endl;
        std::cout << "TRANSMITTANCE : " << materialList[i].transmittance << std::endl;
        std::cout << "IOR : " << materialList[i].ior << std::endl;

        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printSphereData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SPHERES COUNT : " << sphereList.size() << "\n" << std::endl;

    for(unsigned int i = 0; i < sphereList.size(); ++i)
    {
        std::cout << "NAME : " << sphereList[i].name << std::endl;
        std::cout << "RADIUS : " << sphereList[i].radius << std::endl;
        std::cout << "POS X : " << sphereList[i].position.x <<
            " POS Y : " << sphereList[i].position.y <<
            " POS Z : " << sphereList[i].position.z << std::endl;
        std::cout << "MAT NAME : " << sphereList[i].material.name << std::endl;
        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printCameraData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "POS X : " << sceneCamera.position.x <<
        " POS Y : " << sceneCamera.position.y <<
        " POS Z : " << sceneCamera.position.z << std::endl;
    std::cout << "YAW : " << sceneCamera.yaw << std::endl;
    std::cout << "PITCH : " << sceneCamera.pitch << std::endl;
    std::cout << "FOV : " << sceneCamera.fov << std::endl;
    std::cout << "APERTURE RADIUS : " << sceneCamera.apertureRadius << std::endl;
    std::cout << "FOCAL DISTANCE : " << sceneCamera.focalDistance << std::endl;
    std::cout << "\n///////////////\n" << std::endl;
}


void SceneManager::printSettingsData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SKYCOL X : " << sceneSettings.skyColor.x <<
        " SKYCOL Y : " << sceneSettings.skyColor.y <<
        " SKYCOL Z : " << sceneSettings.skyColor.z << std::endl;
    std::cout << "\n///////////////\n" << std::endl;
}


void SceneManager::cleanScene()
{
    cleanMaterialList();
    cleanSphereList();
    cleanMeshList();
}


void SceneManager::cleanMaterialList()
{
    materialList.clear();
    materialList.shrink_to_fit();
}


void SceneManager::cleanSphereList()
{
    sphereList.clear();
    sphereList.shrink_to_fit();
}


void SceneManager::cleanMeshList()
{
    meshList.clear();
    meshList.shrink_to_fit();
}


const std::vector<BSDF>& SceneManager::getMaterialList()
{
    return materialList;
}


const std::vector<Sphere>& SceneManager::getSphereList()
{
    return sphereList;
}


const std::vector<Mesh>& SceneManager::getMeshList()
{
    return meshList;
}


const cameraData &SceneManager::getCamera()
{
    return sceneCamera;
}


const settingsData &SceneManager::getSettings()
{
    return sceneSettings;
}


const XMLScene& SceneManager::getXMLScene()
{
    return xmlScene;
}


const USDScene& SceneManager::getUSDScene()
{
    return usdScene;
}


bool SceneManager::isIntersected(const Ray& ray,
    float& closestSphereDist,
    int& closestSphereID)
{
    float distance;
    float infiniteDistance = closestSphereDist = 1e20;

    for(unsigned int i = 0; i < sphereList.size(); i++)
    {
        if((distance = sphereList[i].computeIntersection(ray)) && distance < closestSphereDist)
        {
            closestSphereDist = distance;
            closestSphereID = i;
        }
    }

    return closestSphereDist < infiniteDistance;
}
