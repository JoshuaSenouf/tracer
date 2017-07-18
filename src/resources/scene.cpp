#include "scene.h"


Scene::Scene()
{
    //std::locale::global(std::locale("en_US.UTF-8")); // So that the "." character is used by std::stof as the separator instead of "," if you are using a french style input for example
    sceneSpheresList = (SphereObject*)malloc(sizeof(SphereObject) * 0);
}


void Scene::loadScene(const char* scenePath)
{
    SphereObject tempSphere;

    std::ifstream sceneReader(scenePath);
    std::string currentLine, objType, tempString;

    while(getline(sceneReader, currentLine))
    {
        if(!currentLine.empty() && !(currentLine[0] == '#'))
        {
            sceneSpheresList = (SphereObject*)realloc(sceneSpheresList, sizeof(SphereObject) * (sceneSphereCount + 1));

            std::stringstream iss(currentLine);

            getline(iss, objType, ';');

            getline(iss, tempString, ';');
            tempSphere.radius = std::stof(tempString);

            getline(iss, tempString, ';');
            tempSphere.position = stringToFloat3(purgeString(tempString));

            getline(iss, tempString, ';');
            tempSphere.color = stringToFloat3(purgeString(tempString));

            getline(iss, tempString, ';');
            tempSphere.emissiveColor = stringToFloat3(purgeString(tempString));

            getline(iss, tempString, ';');
            tempSphere.material = static_cast<materialType>(std::stoi(tempString));

            sceneSpheresList[sceneSphereCount] = tempSphere;
            sceneSphereCount++;
        }
    }

    sceneReader.close();
}


std::string Scene::purgeString(std::string bloatedString)
{
    char badChars[] = "()";

    for (unsigned int i = 0; i < strlen(badChars); ++i)
    {
       bloatedString.erase(std::remove(bloatedString.begin(), bloatedString.end(), badChars[i]), bloatedString.end());
    }

    return bloatedString;
}


glm::vec3 Scene::stringToFloat3(std::string vecString)
{
    int componentCount = 0;
    float vecComponents[3];

    std::string currentValue;
    std::stringstream stream;
    stream.str(vecString);

    while(getline(stream, currentValue, ','))
    {
        vecComponents[componentCount] = std::stof(currentValue);
        componentCount++;
    }

    return glm::vec3(vecComponents[0], vecComponents[1], vecComponents[2]);
}


int Scene::getSphereCount()
{
    return sceneSphereCount;
}

SphereObject* Scene::getSceneSpheresList()
{
    return sceneSpheresList;
}