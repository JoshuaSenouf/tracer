#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>

#include <embree3/rtcore.h>

#include <pxr/usd/usd/stage.h>

#include "object/geometry.h"
// #include "material/material.h"


struct SceneManager
{
    SceneManager();
    SceneManager(
        const std::string &scene_path);

    bool IsSceneValid(
        const std::string &scene_path);
    bool LoadScene(
        const std::string &scene_path);
    bool LoadGeometry();
    bool LoadMeshGeometry();

    pxr::UsdStageRefPtr stage = nullptr;
    RTCDevice device = nullptr;
    // Contains the instanced (single or not) geometry objects. This is the scene we are tracing against.
    RTCScene scene = nullptr;
    std::unordered_map<unsigned int, std::shared_ptr<Geometry>> scene_geom;
    std::mutex mutex;
};

#endif // SCENEMANAGER_H
