#ifndef USDSCENE_H
#define USDSCENE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/base/vt/array.h>

#include <embree3/rtcore.h>

#include "vector.h"
#include "sphere.h"
#include "mesh.h"
#include "geolight.h"
#include "material.h"
#include "render_helper.h"


class USDScene
{
    public:
        USDScene();

        int loadSceneFile(const std::string& scenePath);

        void loadMeshes();

        void getPrimFromType(const std::string &primType,
            const pxr::SdfPath &primPath,
            std::vector<pxr::UsdPrim>& primVector);

    private:
        pxr::UsdStageRefPtr sceneStage;
        RTCScene embreeScene = nullptr;
        RTCDevice embreeDevice = nullptr;
};


#endif // USDSCENE_H
