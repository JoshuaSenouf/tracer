#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "vector.h"
#include "sphere.h"
#include "mesh.h"
#include "light.h"
#include "material.h"
#include "render_helper.h"
#include "xmlscene.h"
#include "usdscene.h"


class SceneManager
{
    public:
        SceneManager();
        SceneManager(const std::string& scenePath);

        int loadScene(const std::string& scenePath);

        void cleanScene();
        void cleanMaterialsList();
        void cleanSpheresList();
        void cleanMeshesList();
        void cleanLightsList();
        void cleanCamera();
        void cleanSettings();

        void printMaterialsData();
        void printSpheresData();
        void printMeshesData();
        void printLightsData();
        void printCameraData();
        void printSettingsData();

        const std::vector<BSDF>& getMaterialsList();
        const std::vector<Sphere>& getSpheresList();
        const std::vector<Mesh>& getMeshesList();
        const std::vector<Light>& getLightsList();
        const cameraData& getCamera();
        const settingsData& getSettings();

        const XMLScene& getXMLScene();
        const USDScene& getUSDScene();

        bool isIntersected(const Ray& ray, float& closestSphereDist, int& closestSphereID);

    private:
        XMLScene xmlScene;
        USDScene usdScene;

        std::vector<BSDF> materialsList;
        std::vector<Sphere> spheresList;
        std::vector<Mesh> meshesList;
        std::vector<Light> lightsList;
        cameraData sceneCamera;
        settingsData sceneSettings;
};

#endif // SCENEMANAGER_H
