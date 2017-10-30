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
            {
                tempMaterial.color = getVectorAttribute(*materialParameter, std::vector<std::string> {"r", "g", "b"});
            }

            else if (materialParameter->Value() == std::string("emissiveColor"))
            {
                tempMaterial.emissiveColor = getVectorAttribute(*materialParameter, std::vector<std::string> {"r", "g", "b"});
            }

            else if (materialParameter->Value() == std::string("fresnel"))
            {
                tempMaterial.fresnel = getVectorAttribute(*materialParameter, std::vector<std::string> {"r", "g", "b"});
            }

            else if (materialParameter->Value() == std::string("roughness"))
            {
                tempMaterial.roughness = getFloatAttribute(*materialParameter, "value");
            }

            else if (materialParameter->Value() == std::string("metalness"))
            {
                tempMaterial.metalness = getFloatAttribute(*materialParameter, "value");
            }

            else if (materialParameter->Value() == std::string("transmittance"))
            {
                tempMaterial.transmittance = getFloatAttribute(*materialParameter, "value");
            }

            else if (materialParameter->Value() == std::string("ior"))
            {
                tempMaterial.ior = getFloatAttribute(*materialParameter, "value");
            }
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
            {
                tempSphere.radius = getFloatAttribute(*sphereParameter, "value");
            }

            else if (sphereParameter->Value() == std::string("position"))
            {
                tempSphere.position = getVectorAttribute(*sphereParameter, std::vector<std::string> {"x", "y", "z"});
            }

            else if (sphereParameter->Value() == std::string("material"))
            {
                std::string tempMaterialName = getStringAttribute(*sphereParameter, "value");

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

}


void Scene::loadConfiguration()
{

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


const std::vector<Sphere>& Scene::getSpheresList()
{
    return spheresList;
}


const std::vector<Mesh>& Scene::getMeshesList()
{
    return meshesList;
}


float Scene::getFloatAttribute(const tinyxml2::XMLNode& objectParameter, const std::string& floatAttr)
{
    float tempFloat;

    objectParameter.ToElement()->QueryFloatAttribute(floatAttr.c_str(), &tempFloat);

    return tempFloat;
}


const std::string Scene::getStringAttribute(const tinyxml2::XMLNode& objectParameter, const std::string& stringAttr)
{
    std::string tempString = objectParameter.ToElement()->Attribute(stringAttr.c_str());

    return tempString;
}


const Vector3 Scene::getVectorAttribute(const tinyxml2::XMLNode& objectParameter, const std::vector<std::string>& vectorAttrList)
{
    Vector3 tempVector;

    objectParameter.ToElement()->QueryFloatAttribute(vectorAttrList.at(0).c_str(), &tempVector.x);
    objectParameter.ToElement()->QueryFloatAttribute(vectorAttrList.at(1).c_str(), &tempVector.y);
    objectParameter.ToElement()->QueryFloatAttribute(vectorAttrList.at(2).c_str(), &tempVector.z);

    return tempVector;
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
