#include "xmlscene.h"


XMLScene::XMLScene()
{

}


int XMLScene::loadSceneFile(const std::string& scenePath)
{
    tinyxml2::XMLError errorOutput = xmlSceneFile.LoadFile(scenePath.c_str());

    if (errorOutput != tinyxml2::XML_SUCCESS)
    {
        std::cout << "ERROR - Failed to open the following XML scene file: " << scenePath << std::endl;

        return false;
    }

    return true;
}


void XMLScene::loadMaterials(std::vector<BSDF>& materialsList)
{
    tinyxml2::XMLElement* materialLevel = xmlSceneFile.FirstChildElement("scene")->FirstChildElement("materials");

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

            else if (materialParameter->Value() == std::string("fresnelColor"))
                getVectorAttribute(tempMaterial.fresnelColor, std::vector<std::string> {"r", "g", "b"}, *materialParameter);

            else if (materialParameter->Value() == std::string("roughness"))
                getFloatAttribute(tempMaterial.roughness, "value", *materialParameter);

            else if (materialParameter->Value() == std::string("metalness"))
                getFloatAttribute(tempMaterial.metalness, "value", *materialParameter);

            else if (materialParameter->Value() == std::string("transmittance"))
                getFloatAttribute(tempMaterial.transmittance, "value", *materialParameter);

            else if (materialParameter->Value() == std::string("ior"))
                getFloatAttribute(tempMaterial.ior, "value", *materialParameter);
        }

        tempMaterial.materialSetup();

        materialsList.push_back(tempMaterial);
    }
}


void XMLScene::loadSpheres(std::vector<Sphere>& spheresList, std::vector<BSDF>& materialsList)
{
    tinyxml2::XMLElement* sphereLevel = xmlSceneFile.FirstChildElement("scene")->FirstChildElement("geometry")->FirstChildElement("spheres");

    for (tinyxml2::XMLElement *sphereElement = sphereLevel->FirstChildElement(); sphereElement; sphereElement = sphereElement->NextSiblingElement())
    {
        Sphere tempSphere;

        tempSphere.name = sphereElement->Attribute("name");

        for (tinyxml2::XMLNode *sphereParameter = sphereElement->FirstChild(); sphereParameter; sphereParameter = sphereParameter->NextSibling())
        {
            if (sphereParameter->Value() == std::string("radius"))
                getDoubleAttribute(tempSphere.radius, "value", *sphereParameter);

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


void XMLScene::loadMeshes(std::vector<Mesh>& meshesList, std::vector<BSDF> &materialsList)
{

}


void XMLScene::loadCamera(cameraData& sceneCamera)
{
    tinyxml2::XMLElement* cameraLevel = xmlSceneFile.FirstChildElement("camera");

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


void XMLScene::loadSettings(settingsData& sceneSettings)
{
    tinyxml2::XMLElement* settingsLevel = xmlSceneFile.FirstChildElement("settings");

    for (tinyxml2::XMLNode *settingsParameter = settingsLevel->FirstChild(); settingsParameter; settingsParameter = settingsParameter->NextSibling())
    {
        if (settingsParameter->Value() == std::string("skyColor"))
        {
            getVectorAttribute(sceneSettings.skyColor, std::vector<std::string> {"r", "g", "b"}, *settingsParameter);
        }
    }
}


void XMLScene::getFloatAttribute(float& floatAttr, const std::string& floatName, const tinyxml2::XMLNode& objectParameter)
{
    objectParameter.ToElement()->QueryFloatAttribute(floatName.c_str(), &floatAttr);
}


void XMLScene::getDoubleAttribute(double& doubleAttr, const std::string& floatName, const tinyxml2::XMLNode& objectParameter)
{
    objectParameter.ToElement()->QueryDoubleAttribute(floatName.c_str(), &doubleAttr);
}


void XMLScene::getStringAttribute(std::string& stringAttr, const std::string& stringName, const tinyxml2::XMLNode& objectParameter)
{
    stringAttr = objectParameter.ToElement()->Attribute(stringName.c_str());
}


void XMLScene::getVectorAttribute(Vector3& vectorAttr, const std::vector<std::string>& vectorNameList, const tinyxml2::XMLNode& objectParameter)
{
    objectParameter.ToElement()->QueryFloatAttribute(vectorNameList.at(0).c_str(), &vectorAttr.x);
    objectParameter.ToElement()->QueryFloatAttribute(vectorNameList.at(1).c_str(), &vectorAttr.y);
    objectParameter.ToElement()->QueryFloatAttribute(vectorNameList.at(2).c_str(), &vectorAttr.z);
}
