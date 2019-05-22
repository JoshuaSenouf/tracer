#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <mutex>

#include "usd_helper.h"
#include "embree_helper.h"
#include "render_helper.h"

#include "geometry.h"


class SceneManager
{
    public:
        SceneManager();
        SceneManager(const std::string& scenePath);

        bool isSceneValid(const std::string& scenePath);
        bool loadScene(const std::string& scenePath);
        // bool loadCamera();
        // bool loadMaterials();
        bool loadGeometry();
        bool loadMeshGeometry();
        // bool loadCurveGeometry();
        // bool loadPrimitiveGeometry();

        const pxr::UsdStageRefPtr& getStage();
        const RTCDevice& getDevice();
        const RTCScene& getRootScene();

    private:
        pxr::UsdStageRefPtr stage = nullptr;
        RTCDevice device = nullptr;
        RTCScene rootScene = nullptr; // Contains the instanced (single or not) geometry objects. This is the scene we are tracing against.

        std::mutex geometryMutex;

        std::vector<std::shared_ptr<Geometry>> sceneGeometry;
};

#endif // SCENEMANAGER_H
