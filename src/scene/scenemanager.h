#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <mutex>
#include <unordered_map>

#include "usd_helper.h"
#include "embree_helper.h"
#include "render_helper.h"

#include "geometry.h"


struct SceneManager
{
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

    pxr::UsdStageRefPtr _stage = nullptr;
    RTCDevice _device = nullptr;
    RTCScene _scene = nullptr; // Contains the instanced (single or not) geometry objects. This is the scene we are tracing against.

    std::mutex _sceneMutex;

    std::unordered_map<unsigned int, std::shared_ptr<Geometry>> _sceneGeom;

};

#endif // SCENEMANAGER_H
