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

        xmlScene.loadMaterials(materialsList);
        xmlScene.loadSpheres(spheresList, materialsList);
        xmlScene.loadMeshes(meshesList, materialsList);
        xmlScene.loadCamera(sceneCamera);
        xmlScene.loadSettings(sceneSettings);
    }
    else if (std::size_t(scenePath.rfind(std::string(".usd")) != std::string::npos)
             || std::size_t(scenePath.rfind(std::string(".usda")) != std::string::npos)
             || std::size_t(scenePath.rfind(std::string(".usdc")) != std::string::npos))
    {
        if (!usdScene.loadSceneFile(scenePath))
            return false;

        usdScene.loadMaterials(materialsList);
        usdScene.loadSpheres(spheresList, materialsList);
        usdScene.loadMeshes(meshesList, materialsList);
        usdScene.loadCamera(sceneCamera);
        usdScene.loadSettings(sceneSettings);
    }
    else
    {
        std::cout << "ERROR - The following file is neither a XML or an USD scene: " << scenePath << std::endl;
        return false;
    }
}


void SceneManager::printMaterialsData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "MATERIALS COUNT : " << materialsList.size() << "\n" << std::endl;

    for(int i = 0; i < materialsList.size(); ++i)
    {
        std::cout << "NAME : " << materialsList[i].name << std::endl;
        std::cout << "COL X : " << materialsList[i].color.x << " COL Y : " << materialsList[i].color.y << " COL Z : " << materialsList[i].color.z << std::endl;
        std::cout << "EMI X : " << materialsList[i].emissiveColor.x << " EMI Y : " << materialsList[i].emissiveColor.y << " EMI Z : " << materialsList[i].emissiveColor.z << std::endl;
        std::cout << "FRESNEL X : " << materialsList[i].fresnelColor.x << " FRESNEL Y : " << materialsList[i].fresnelColor.y << " FRESNEL Z : " << materialsList[i].fresnelColor.z << std::endl;
        std::cout << "ROUGHNESS : " << materialsList[i].roughness << std::endl;
        std::cout << "METALNESS : " << materialsList[i].metalness << std::endl;
        std::cout << "TRANSMITTANCE : " << materialsList[i].transmittance << std::endl;
        std::cout << "IOR : " << materialsList[i].ior << std::endl;

        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printSpheresData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SPHERES COUNT : " << spheresList.size() << "\n" << std::endl;

    for(int i = 0; i < spheresList.size(); ++i)
    {
        std::cout << "NAME : " << spheresList[i].name << std::endl;
        std::cout << "RADIUS : " << spheresList[i].radius << std::endl;
        std::cout << "POS X : " << spheresList[i].position.x << " POS Y : " << spheresList[i].position.y << " POS Z : " << spheresList[i].position.z << std::endl;
        std::cout << "MAT NAME : " << spheresList[i].material.name << std::endl;
        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printCameraData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "POS X : " << sceneCamera.position.x << " POS Y : " << sceneCamera.position.x << " POS Z : " << sceneCamera.position.x << std::endl;
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
    std::cout << "SKYCOL X : " << sceneSettings.skyColor.x << " SKYCOL Y : " << sceneSettings.skyColor.y << " SKYCOL Z : " << sceneSettings.skyColor.z << std::endl;
    std::cout << "\n///////////////\n" << std::endl;
}


void SceneManager::cleanScene()
{
    cleanMaterialsList();
    cleanSpheresList();
    cleanMeshesList();
}


void SceneManager::cleanMaterialsList()
{
    materialsList.clear();
    materialsList.shrink_to_fit();
}


void SceneManager::cleanSpheresList()
{
    spheresList.clear();
    spheresList.shrink_to_fit();
}


void SceneManager::cleanMeshesList()
{
    meshesList.clear();
    meshesList.shrink_to_fit();
}


const std::vector<BSDF>& SceneManager::getMaterialsList()
{
    return materialsList;
}


const std::vector<Sphere>& SceneManager::getSpheresList()
{
    return spheresList;
}


const std::vector<Mesh>& SceneManager::getMeshesList()
{
    return meshesList;
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


bool SceneManager::isIntersected(const Ray& ray, float& closestSphereDist, int& closestSphereID)
{
    float distance;
    float infiniteDistance = closestSphereDist = 1e20;

    for(int i = 0; i < spheresList.size(); i++)
    {
        if((distance = spheresList[i].computeIntersection(ray)) && distance < closestSphereDist)
        {
            closestSphereDist = distance;
            closestSphereID = i;
        }
    }

    return closestSphereDist < infiniteDistance;
}
