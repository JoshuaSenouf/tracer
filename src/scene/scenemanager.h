#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include <embree3/rtcore.h>

#include "vector.h"
#include "sphere.h"
#include "mesh.h"
#include "geolight.h"
#include "material.h"
#include "render_helper.h"
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

        std::vector<BSDF>& getMaterialList();
        std::vector<Sphere>& getSphereList();
        std::vector<Mesh>& getMeshList();
        std::vector<GeoLight>& getLightList();
        cameraData& getCamera();
        settingsData& getSettings();
        USDScene& getUSDScene();

        bool isIntersected(Ray& ray,
            float& closestGeoDist,
            int& closestGeoID,
            bool& isLightSource);

    private:
        USDScene usdScene;
        // ??? embreeScene;

        std::vector<BSDF> materialList;
        std::vector<Sphere> sphereList;
        std::vector<Mesh> meshList;
        std::vector<GeoLight> lightList;
        cameraData sceneCamera;
        settingsData sceneSettings;
};

#endif // SCENEMANAGER_H
