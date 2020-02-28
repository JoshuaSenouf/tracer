#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include "buffer.h"
#include "camera.h"
#include "integrator.h"
#include "render_helper.h"
#include "scenemanager.h"

#include "debug.h"
#include "diffuse.h"
#include "normal.h"
#include "occlusion.h"
#include "position.h"
#include "udpt.h"


struct TracerRenderer
{
    TracerRenderer();

    void Trace(const RenderGlobals& globals,
        SceneManager& scene,
        Camera& camera,
        Buffer& buffer,
        int iterations);

    private:
        std::vector<std::shared_ptr<Integrator>> _integrators {
            std::make_shared<UDPTIntegrator>(),
            std::make_shared<DiffuseIntegrator>(),
            std::make_shared<OcclusionIntegrator>(),
            std::make_shared<PositionIntegrator>(),
            std::make_shared<NormalIntegrator>(),
            std::make_shared<DebugIntegrator>()
        };
};

#endif // RENDERER_H
