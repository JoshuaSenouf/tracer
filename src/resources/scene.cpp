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
                float sphereRadius;

                sphereParameter->ToElement()->QueryFloatAttribute("value", &sphereRadius);

                tempSphere.radius = sphereRadius;
            }

            if (sphereParameter->Value() == std::string("position"))
            {
                Vector3 spherePosition;

                sphereParameter->ToElement()->QueryFloatAttribute("x", &spherePosition.x);
                sphereParameter->ToElement()->QueryFloatAttribute("y", &spherePosition.y);
                sphereParameter->ToElement()->QueryFloatAttribute("z", &spherePosition.z);

                tempSphere.position = spherePosition;
            }

            else if (sphereParameter->Value() == std::string("color"))
            {
                Vector3 sphereColor;

                sphereParameter->ToElement()->QueryFloatAttribute("r", &sphereColor.x);
                sphereParameter->ToElement()->QueryFloatAttribute("g", &sphereColor.y);
                sphereParameter->ToElement()->QueryFloatAttribute("b", &sphereColor.z);

                tempSphere.color = sphereColor;
            }

            else if (sphereParameter->Value() == std::string("emissiveColor"))
            {
                Vector3 sphereEmissive;

                sphereParameter->ToElement()->QueryFloatAttribute("r", &sphereEmissive.x);
                sphereParameter->ToElement()->QueryFloatAttribute("g", &sphereEmissive.y);
                sphereParameter->ToElement()->QueryFloatAttribute("b", &sphereEmissive.z);

                tempSphere.emissiveColor = sphereEmissive;
            }

            if (sphereParameter->Value() == std::string("material"))
            {
                float sphereMaterial;

                sphereParameter->ToElement()->QueryFloatAttribute("value", &sphereMaterial);

                tempSphere.materialID = sphereMaterial;
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
