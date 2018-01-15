#include "scene.h"


Scene::Scene()
{

}


Scene::Scene(const std::string& scenePath)
{
    loadSceneFile(scenePath);
}


int Scene::loadSceneFile(const std::string& scenePath)
{
    cleanScene();

    tinyxml2::XMLError errorOutput = sceneFile.LoadFile(scenePath.c_str());

    if (errorOutput != tinyxml2::XML_SUCCESS)
    {
        std::cout << "ERROR - Failed to open the following scene file : " << scenePath << std::endl;

        return 0;
    }

    loadMaterials();
    loadSpheres();
    loadCamera();
    loadSettings();
}


void Scene::loadMaterials()
{
    tinyxml2::XMLElement* materialLevel = sceneFile.FirstChildElement("scene")->FirstChildElement("materials");

    for (tinyxml2::XMLElement *materialElement = materialLevel->FirstChildElement(); materialElement; materialElement = materialElement->NextSiblingElement())
    {
        BSDF tempMaterial;

        tempMaterial.name = materialElement->Attribute("name");

        for (tinyxml2::XMLNode *materialParameter = materialElement->FirstChild(); materialParameter; materialParameter = materialParameter->NextSibling())
        {
            if (materialParameter->Value() == std::string("color"))
                getVectorAttribute(tempMaterial.color, std::vector<std::string> {"r", "g", "b"}, *materialParameter);

            else if (materialParameter->Value() == std::string("emissiveColor"))
                getVectorAttribute(tempMaterial.emissiveColor, std::vector<std::string> {"r", "g", "b"}, *materialParameter);

            else if (materialParameter->Value() == std::string("fresnel"))
                getVectorAttribute(tempMaterial.fresnel, std::vector<std::string> {"r", "g", "b"}, *materialParameter);

            else if (materialParameter->Value() == std::string("roughness"))
                getFloatAttribute(tempMaterial.roughness, "value", *materialParameter);

            else if (materialParameter->Value() == std::string("metalness"))
                getFloatAttribute(tempMaterial.metalness, "value", *materialParameter);

            else if (materialParameter->Value() == std::string("transmittance"))
                getFloatAttribute(tempMaterial.transmittance, "value", *materialParameter);

            else if (materialParameter->Value() == std::string("ior"))
                getFloatAttribute(tempMaterial.ior, "value", *materialParameter);
        }

        materialsList.push_back(tempMaterial);
    }
}


void Scene::loadSpheres()
{
    tinyxml2::XMLElement* sphereLevel = sceneFile.FirstChildElement("scene")->FirstChildElement("geometry")->FirstChildElement("spheres");

    for (tinyxml2::XMLElement *sphereElement = sphereLevel->FirstChildElement(); sphereElement; sphereElement = sphereElement->NextSiblingElement())
    {
        Sphere tempSphere;

        tempSphere.name = sphereElement->Attribute("name");

        for (tinyxml2::XMLNode *sphereParameter = sphereElement->FirstChild(); sphereParameter; sphereParameter = sphereParameter->NextSibling())
        {
            if (sphereParameter->Value() == std::string("radius"))
                getFloatAttribute(tempSphere.radius, "value", *sphereParameter);

            else if (sphereParameter->Value() == std::string("position"))
                 getVectorAttribute(tempSphere.position, std::vector<std::string> {"x", "y", "z"}, *sphereParameter);

            else if (sphereParameter->Value() == std::string("material"))
            {
                std::string tempMaterialName;

                getStringAttribute(tempMaterialName, "value", *sphereParameter);

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


void Scene::loadMeshes()
{

}


void Scene::loadCamera()
{
    tinyxml2::XMLElement* cameraLevel = sceneFile.FirstChildElement("camera");

    for (tinyxml2::XMLNode *cameraParameter = cameraLevel->FirstChild(); cameraParameter; cameraParameter = cameraParameter->NextSibling())
    {
        if (cameraParameter->Value() == std::string("position"))
            getVectorAttribute(sceneCamera.position, std::vector<std::string> {"x", "y", "z"}, *cameraParameter);

        else if (cameraParameter->Value() == std::string("yaw"))
            getFloatAttribute(sceneCamera.yaw, "value", *cameraParameter);

        else if (cameraParameter->Value() == std::string("pitch"))
            getFloatAttribute(sceneCamera.pitch, "value", *cameraParameter);

        else if (cameraParameter->Value() == std::string("fov"))
            getFloatAttribute(sceneCamera.fov, "value", *cameraParameter);

        else if (cameraParameter->Value() == std::string("apertureRadius"))
            getFloatAttribute(sceneCamera.apertureRadius, "value", *cameraParameter);

        else if (cameraParameter->Value() == std::string("focalDistance"))
            getFloatAttribute(sceneCamera.focalDistance, "value", *cameraParameter);
    }
}


void Scene::loadSettings()
{
    tinyxml2::XMLElement* settingsLevel = sceneFile.FirstChildElement("settings");

    for (tinyxml2::XMLNode *settingsParameter = settingsLevel->FirstChild(); settingsParameter; settingsParameter = settingsParameter->NextSibling())
    {
        if (settingsParameter->Value() == std::string("skyColor"))
        {
            getVectorAttribute(sceneSettings.skyColor, std::vector<std::string> {"r", "g", "b"}, *settingsParameter);
        }
    }
}


void Scene::printMaterialsData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "MATERIALS COUNT : " << materialsList.size() << "\n" << std::endl;

    for(int i = 0; i < materialsList.size(); ++i)
    {
        std::cout << "NAME : " << materialsList[i].name << std::endl;
        std::cout << "COL X : " << materialsList[i].color.x << " COL Y : " << materialsList[i].color.y << " COL Z : " << materialsList[i].color.z << std::endl;
        std::cout << "EMI X : " << materialsList[i].emissiveColor.x << " EMI Y : " << materialsList[i].emissiveColor.y << " EMI Z : " << materialsList[i].emissiveColor.z << std::endl;
        std::cout << "FRESNEL X : " << materialsList[i].fresnel.x << " FRESNEL Y : " << materialsList[i].fresnel.y << " FRESNEL Z : " << materialsList[i].fresnel.z << std::endl;
        std::cout << "ROUGHNESS : " << materialsList[i].roughness << std::endl;
        std::cout << "METALNESS : " << materialsList[i].metalness << std::endl;
        std::cout << "TRANSMITTANCE : " << materialsList[i].transmittance << std::endl;
        std::cout << "IOR : " << materialsList[i].ior << std::endl;

        std::cout << "\n///////////////\n" << std::endl;
    }
}


void Scene::printSpheresData()
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


void Scene::printCameraData()
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


void Scene::printSettingsData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SKYCOL X : " << sceneSettings.skyColor.x << " SKYCOL Y : " << sceneSettings.skyColor.y << " SKYCOL Z : " << sceneSettings.skyColor.z << std::endl;
    std::cout << "\n///////////////\n" << std::endl;
}


void Scene::cleanScene()
{
    cleanMaterialsList();
    cleanSpheresList();
    cleanMeshesList();
}


void Scene::cleanMaterialsList()
{
    materialsList.clear();
    materialsList.shrink_to_fit();
}


void Scene::cleanSpheresList()
{
    spheresList.clear();
    spheresList.shrink_to_fit();
}


void Scene::cleanMeshesList()
{
    meshesList.clear();
    meshesList.shrink_to_fit();
}


const std::vector<BSDF>& Scene::getMaterialsList()
{
    return materialsList;
}


const std::vector<Sphere>& Scene::getSpheresList()
{
    return spheresList;
}


const std::vector<Mesh>& Scene::getMeshesList()
{
    return meshesList;
}


const cameraData &Scene::getCamera()
{
    return sceneCamera;
}


const settingsData &Scene::getSettings()
{
    return sceneSettings;
}


void Scene::getFloatAttribute(float& floatAttr, const std::string& floatName, const tinyxml2::XMLNode& objectParameter)
{
    objectParameter.ToElement()->QueryFloatAttribute(floatName.c_str(), &floatAttr);
}


void Scene::getStringAttribute(std::string& stringAttr, const std::string& stringName, const tinyxml2::XMLNode& objectParameter)
{
    stringAttr = objectParameter.ToElement()->Attribute(stringName.c_str());
}


void Scene::getVectorAttribute(Vector3& vectorAttr, const std::vector<std::string>& vectorNameList, const tinyxml2::XMLNode& objectParameter)
{
    objectParameter.ToElement()->QueryFloatAttribute(vectorNameList.at(0).c_str(), &vectorAttr.x);
    objectParameter.ToElement()->QueryFloatAttribute(vectorNameList.at(1).c_str(), &vectorAttr.y);
    objectParameter.ToElement()->QueryFloatAttribute(vectorNameList.at(2).c_str(), &vectorAttr.z);
}


bool Scene::isIntersected(const Ray& ray, float& closestSphereDist, int& closestSphereID)
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
