#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "object.h"
#include "vector.h"


class Scene
{
    public:
        Scene();

        void loadScene(std::string scenePath);
        std::string purgeString(std::string bloatedString);
        Vector3 stringToFloat3(std::string vecString);

        std::vector<SphereObject> getSceneSpheresList();

    private:
        std::vector<SphereObject> sceneSpheresList;
};

#endif // SCENEPARSER_H
