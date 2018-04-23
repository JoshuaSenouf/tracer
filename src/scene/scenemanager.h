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
#include "geolight.h"
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
        void cleanMaterialList();
        void cleanSphereList();
        void cleanMeshList();
        void cleanLightList();
        void cleanCamera();
        void cleanSettings();

        void printMaterialData();
        void printSphereData();
        void printMeshData();
        void printLightData();
        void printCameraData();
        void printSettingsData();

        const std::vector<BSDF>& getMaterialList();
        const std::vector<Sphere>& getSphereList();
        const std::vector<Mesh>& getMeshList();
        const std::vector<GeoLight>& getLightList();
        const cameraData& getCamera();
        const settingsData& getSettings();
        const XMLScene& getXMLScene();
        const USDScene& getUSDScene();

        bool isIntersected(Ray& ray,
            float& closestSphereDist,
            int& closestSphereID);

    private:
        XMLScene xmlScene;
        USDScene usdScene;

        std::vector<BSDF> materialList;
        std::vector<Sphere> sphereList;
        std::vector<Mesh> meshList;
        std::vector<GeoLight> lightList;
        cameraData sceneCamera;
        settingsData sceneSettings;
};

#endif // SCENEMANAGER_H
