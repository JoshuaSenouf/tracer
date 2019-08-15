#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include <spdlog/spdlog.h>

#include "buffer.h"
#include "camera.h"
#include "integrator.h"
#include "ray.h"
#include "scenemanager.h"
#include "sampler.h"

#include "udpt.h"
#include "diffuse.h"
#include "occlusion.h"
#include "position.h"
#include "normal.h"
#include "debug.h"

#include "render_helper.h"
#include "tbb_helper.h"


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
