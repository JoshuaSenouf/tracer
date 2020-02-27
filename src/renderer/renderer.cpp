#include <spdlog/spdlog.h>

#include <tbb/blocked_range3d.h>
#include <tbb/parallel_for.h>

#include "ray.h"
#include "renderer.h"
#include "sampler.h"


TracerRenderer::TracerRenderer()
{
    spdlog::trace("TracerRenderer::TracerRenderer()");
}

void TracerRenderer::Trace(const RenderGlobals& globals,
    SceneManager &scene,
    Camera& camera,
    Buffer& buffer,
    int iterations)
{
    spdlog::trace("TracerRenderer::Trace()");

    tbb::parallel_for(tbb::blocked_range<int>(0, globals.height),
        [&](tbb::blocked_range<int> height_range)
    {
        for (int pixelY = height_range.begin(); pixelY < height_range.end(); ++pixelY)
        {
            Sampler sampler;

            for (int pixelX = 0; pixelX < globals.width; ++pixelX)
            {
                // We setup all the necessary data describing the current sample.
                PixelSample sample(sampler);
                sample.pixelX = pixelX;
                sample.pixelY = pixelY;
                sample.pixelIdx = pixelX + pixelY * globals.width;
                sample.samples = globals.samples;

                // The final pixel color of the sample we are computing that will be added and averaged to the buffer.
                embree::Vec3f color(0.0f);

                for (sample.sampleIdx = 0; sample.sampleIdx < globals.samples; ++sample.sampleIdx)
                {
                    Ray ray(camera, sample);

                    color += (embree::Vec3f(buffer._data[sample.pixelIdx] * (iterations - 1)) +
                        _integrators[globals.integratorID]->GetPixelColor(ray,
                            sample,
                            scene,
                            globals)) * (1.0f / globals.samples);

                    // Random noise test
                    // color += (embree::Vec3f(buffer._data[sample.pixelIdx] * (iterations - 1)) +
                    //     embree::Vec3f(sample.sampler.Uniform1D(),
                    //         sample.sampler.Uniform1D(),
                    //         sample.sampler.Uniform1D())) * (1.0f / globals.samples);
                }

                buffer._data[sample.pixelIdx] = color / iterations;
            }
        }
    });

    spdlog::info("TracerRenderer::Trace() - "
        "Rendered iteration number " + std::to_string(iterations) + ".");
}
