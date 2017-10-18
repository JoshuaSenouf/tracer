#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "sphere.h"
#include "vector.h"


class Scene
{
    public:
        Scene();

        void loadScene(std::string scenePath);
        std::string purgeString(std::string bloatedString);
        Vector3 stringToFloat3(std::string vecString);

        std::vector<Sphere> getSceneSpheresList();

    private:
        std::vector<Sphere> sceneSpheresList;
};

#endif // SCENEPARSER_H
