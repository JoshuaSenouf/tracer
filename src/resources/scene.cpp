#include "scene.h"


Scene::Scene()
{
    //std::locale::global(std::locale("en_US.UTF-8")); // So that the "." character is used by std::stof as the separator instead of "," if you are using a french style input for example
}


void Scene::loadScene(std::string scenePath)
{
    Sphere tempSphere;

    std::ifstream sceneReader(scenePath);
    std::string currentLine, objType, tempString;

    while(getline(sceneReader, currentLine))
    {
        if(!currentLine.empty() && !(currentLine[0] == '#'))
        {
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

            sceneSpheresList.push_back(tempSphere);
        }
    }

    sceneReader.close();
}


std::string Scene::purgeString(std::string bloatedString)
{
    std::string badChars = "()";

    for (unsigned int i = 0; i < badChars.length(); ++i)
    {
        bloatedString.erase(std::remove(bloatedString.begin(), bloatedString.end(), badChars[i]), bloatedString.end());
    }

    return bloatedString;
}


Vector3 Scene::stringToFloat3(std::string vecString)
{
    int componentCount = 0;
    std::vector<float> vecComponents(3);

    std::string currentValue;
    std::stringstream stream;
    stream.str(vecString);

    while(getline(stream, currentValue, ','))
    {
        vecComponents[componentCount] = std::stof(currentValue);
        componentCount++;
    }

    return Vector3(vecComponents[0], vecComponents[1], vecComponents[2]);
}


std::vector<Sphere> Scene::getSceneSpheresList()
{
    return sceneSpheresList;
}
