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
        //xmlScene.loadLights(lightList, sphereList, materialList);
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
        usdScene.loadLights(lightList, sphereList, materialList);
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
    std::cout << "MATERIALS COUNT: " << materialList.size() << "\n" << std::endl;

    for(unsigned int i = 0; i < materialList.size(); ++i)
    {
        std::cout << "NAME: " << materialList[i].getName() << std::endl;
        std::cout << "COL X: " << materialList[i].getColor().x <<
            " COL Y: " << materialList[i].getColor().y <<
            " COL Z: " << materialList[i].getColor().z << std::endl;
        std::cout << "EMI X: " << materialList[i].getEmissiveColor().x <<
            " EMI Y: " << materialList[i].getEmissiveColor().y <<
            " EMI Z: " << materialList[i].getEmissiveColor().z << std::endl;
        std::cout << "FRESNEL X: " << materialList[i].getFresnelColor().x <<
            " FRESNEL Y: " << materialList[i].getFresnelColor().y <<
            " FRESNEL Z: " << materialList[i].getFresnelColor().z << std::endl;
        std::cout << "ROUGHNESS: " << materialList[i].getRoughness() << std::endl;
        std::cout << "METALNESS: " << materialList[i].getMetalness() << std::endl;
        std::cout << "TRANSMITTANCE: " << materialList[i].getTransmittance() << std::endl;
        std::cout << "IOR: " << materialList[i].getIOR() << std::endl;

        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printSphereData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SPHERES COUNT: " << sphereList.size() << "\n" << std::endl;

    for(unsigned int i = 0; i < sphereList.size(); ++i)
    {
        std::cout << "NAME: " << sphereList[i].getName() << std::endl;
        std::cout << "RADIUS: " << sphereList[i].getRadius() << std::endl;
        std::cout << "POS X: " << sphereList[i].getPosition().x <<
            " POS Y: " << sphereList[i].getPosition().y <<
            " POS Z: " << sphereList[i].getPosition().z << std::endl;
        std::cout << "MAT NAME: " << sphereList[i].getMaterial().getName() << std::endl;
        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printMeshData()
{
    
}


void SceneManager::printLightData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "LIGHTS COUNT: " << lightList.size() << "\n" << std::endl;

    for(unsigned int i = 0; i < lightList.size(); ++i)
    {
        std::cout << "GEOMETRY: " << lightList[i].getGeometry().getName() << std::endl;
        std::cout << "MATERIAL: " << lightList[i].getMaterial().getName() << std::endl;
        std::cout << "\n///////////////\n" << std::endl;
    }
}


void SceneManager::printCameraData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "POS X: " << sceneCamera.position.x <<
        " POS Y: " << sceneCamera.position.y <<
        " POS Z: " << sceneCamera.position.z << std::endl;
    std::cout << "YAW: " << sceneCamera.yaw << std::endl;
    std::cout << "PITCH: " << sceneCamera.pitch << std::endl;
    std::cout << "FOV: " << sceneCamera.FOV << std::endl;
    std::cout << "APERTURE RADIUS: " << sceneCamera.apertureRadius << std::endl;
    std::cout << "FOCAL DISTANCE: " << sceneCamera.focalDistance << std::endl;
    std::cout << "\n///////////////\n" << std::endl;
}


void SceneManager::printSettingsData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SKYCOL X: " << sceneSettings.skyColor.x <<
        " SKYCOL Y: " << sceneSettings.skyColor.y <<
        " SKYCOL Z: " << sceneSettings.skyColor.z << std::endl;
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


void SceneManager::cleanLightList()
{
    sphereList.clear();
    sphereList.shrink_to_fit();
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


const std::vector<GeoLight>& SceneManager::getLightList()
{
    return lightList;
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


bool SceneManager::isIntersected(Ray& ray,
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
