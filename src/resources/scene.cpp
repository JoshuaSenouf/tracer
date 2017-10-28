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

    loadSpheres();
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

            if (sphereParameter->Value() == std::string("position"))
            {
                tempSphere.position = getVectorAttribute(*sphereParameter, std::vector<std::string> {"x", "y", "z"});
            }

            else if (sphereParameter->Value() == std::string("color"))
            {
                tempSphere.color = getVectorAttribute(*sphereParameter, std::vector<std::string> {"r", "g", "b"});
            }

            else if (sphereParameter->Value() == std::string("emissiveColor"))
            {
                tempSphere.emissiveColor = getVectorAttribute(*sphereParameter, std::vector<std::string> {"r", "g", "b"});
            }

            if (sphereParameter->Value() == std::string("material"))
            {
                tempSphere.materialID = getFloatAttribute(*sphereParameter, "value");
            }
        }

        spheresList.push_back(tempSphere);
    }
}


void Scene::loadMeshes()
{

}


void Scene::loadMaterials()
{

}


void Scene::loadCamera()
{

}


void Scene::loadConfiguration()
{

}


void Scene::printSpheresData()
{
    std::cout << "\n///////////////\n" << std::endl;
    std::cout << "SPHERECOUNT : " << spheresList.size() << "\n" << std::endl;

    for(int i = 0; i < spheresList.size(); ++i)
    {
        std::cout << "NAME : " << spheresList[i].name << std::endl;
        std::cout << "RADIUS : " << spheresList[i].radius << std::endl;
        std::cout << "POS X : " << spheresList[i].position.x << " POS Y : " << spheresList[i].position.y << " POS Z : " << spheresList[i].position.z << std::endl;
        std::cout << "COL R : " << spheresList[i].color.x << " COL G : " << spheresList[i].color.y << " COL B: " << spheresList[i].color.z << std::endl;
        std::cout << "EMI R : " << spheresList[i].emissiveColor.x << " EMI G : " << spheresList[i].emissiveColor.y << " EMI B : " << spheresList[i].emissiveColor.z << std::endl;
        std::cout << "MATERIALID : " << spheresList[i].materialID << std::endl;
        std::cout << "\n///////////////\n" << std::endl;
    }
}


void Scene::cleanScene()
{
    cleanSpheresList();
    cleanMeshesList();
    cleanMaterialsList();
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


void Scene::cleanMaterialsList()
{

}


const std::vector<Sphere>& Scene::getSpheresList()
{
    return spheresList;
}


const std::vector<Mesh>& Scene::getMeshesList()
{
    return meshesList;
}


float Scene::getFloatAttribute(const tinyxml2::XMLNode& objectParameter, std::string floatAttr)
{
    float tempFloat;

    objectParameter.ToElement()->QueryFloatAttribute(floatAttr.c_str(), &tempFloat);

    return tempFloat;
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
