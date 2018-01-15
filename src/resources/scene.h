#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "tinyxml2.h"

#include "vector.h"
#include "sphere.h"
#include "mesh.h"
#include "material.h"


struct cameraData
{
    Vector3 position;
    float yaw;
    float pitch;
    float fov;
    float apertureRadius;
    float focalDistance;
};

struct settingsData
{
    Vector3 skyColor;
};


class Scene
{
    public:
        Scene();
        Scene(const std::string& scenePath);

        int loadSceneFile(const std::string& scenePath);
        void loadMaterials();
        void loadSpheres();
        void loadMeshes();
        void loadCamera();
        void loadSettings();
        void cleanScene();
        void cleanMaterialsList();
        void cleanSpheresList();
        void cleanMeshesList();
        void cleanCamera();
        void cleanSettings();
        void printMaterialsData();
        void printSpheresData();
        void printCameraData();
        void printSettingsData();

        const std::vector<BSDF>& getMaterialsList();
        const std::vector<Sphere>& getSpheresList();
        const std::vector<Mesh>& getMeshesList();
        const cameraData& getCamera();
        const settingsData& getSettings();

        void getFloatAttribute(float& floatAttr, const std::string& floatName, const tinyxml2::XMLNode& objectParameter);
        void getStringAttribute(std::string& stringAttr, const std::string& stringName, const tinyxml2::XMLNode& objectParameter);
        void getVectorAttribute(Vector3& vectorAttr, const std::vector<std::string>& vectorNameList, const tinyxml2::XMLNode& objectParameter);

        bool isIntersected(const Ray& ray, float& closestSphereDist, int& closestSphereID);

    private:
        tinyxml2::XMLDocument sceneFile;

        std::vector<BSDF> materialsList;
        std::vector<Sphere> spheresList;
        std::vector<Mesh> meshesList;
        cameraData sceneCamera;
        settingsData sceneSettings;
};

#endif // SCENEPARSER_H
