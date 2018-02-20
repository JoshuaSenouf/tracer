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

        const XMLScene& getXMLScene();
        const USDScene& getUSDScene();

        bool isIntersected(const Ray& ray, float& closestSphereDist, int& closestSphereID);

    private:
        XMLScene xmlScene;
        USDScene usdScene;

        std::vector<BSDF> materialsList;
        std::vector<Sphere> spheresList;
        std::vector<Mesh> meshesList;
        cameraData sceneCamera;
        settingsData sceneSettings;
};

#endif // SCENEMANAGER_H
