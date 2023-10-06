#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "camera/camera.h"
#include "integrator/debug.h"
#include "integrator/diffuse.h"
#include "integrator/integrator.h"
#include "integrator/normal.h"
#include "integrator/occlusion.h"
#include "integrator/position.h"
#include "integrator/udpt.h"
#include "object/buffer.h"
#include "scene/scenemanager.h"
#include "utility/render.h"


class TracerRenderer
{
    public:
        TracerRenderer();

        void Trace(
            const RenderGlobals &globals,
            SceneManager &scene_manager,
            Camera &camera,
            Buffer &buffer,
            int iterations);

        unsigned int integrator_id = kUDPT;
    private:
        std::vector<std::shared_ptr<Integrator>> integrators_ {
            std::make_shared<UDPTIntegrator>(),
            std::make_shared<DiffuseIntegrator>(),
            std::make_shared<OcclusionIntegrator>(),
            std::make_shared<PositionIntegrator>(),
            std::make_shared<NormalIntegrator>(),
            std::make_shared<DebugIntegrator>()
        };
};

#endif // RENDERER_H
