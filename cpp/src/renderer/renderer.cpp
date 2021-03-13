#include <spdlog/spdlog.h>

#include <tbb/blocked_range3d.h>
#include <tbb/parallel_for.h>

#include "object/ray.h"
#include "sampling/sampler.h"

#include "renderer/renderer.h"

TracerRenderer::TracerRenderer()
{
    spdlog::trace("TracerRenderer::TracerRenderer()");
}

void TracerRenderer::Trace(
    const RenderGlobals &globals,
    SceneManager &scene_manager,
    Camera &camera,
    Buffer &buffer,
    int iterations)
{
    spdlog::trace("TracerRenderer::Trace()");

    tbb::parallel_for(tbb::blocked_range<int>(0, globals.height), [&](tbb::blocked_range<int> height_range)
    {
        for (int pixel_y = height_range.begin(); pixel_y < height_range.end(); ++pixel_y)
        {
            Sampler sampler;

            for (int pixel_x = 0; pixel_x < globals.width; ++pixel_x)
            {
                // We setup all the necessary data describing the current pixel_sample.
                PixelSample pixel_sample(sampler);
                pixel_sample.pixel_x = pixel_x;
                pixel_sample.pixel_y = pixel_y;
                pixel_sample.pixel_idx = pixel_x + pixel_y * globals.width;
                pixel_sample.samples = globals.samples;

                // The final pixel color of the sample we are computing that will be added and averaged to the buffer.
                embree::Vec3f pixel_color(0.0f);

                for (pixel_sample.sample_idx = 0; pixel_sample.sample_idx < globals.samples; ++pixel_sample.sample_idx)
                {
                    Ray ray(camera, pixel_sample);

                    pixel_color += (embree::Vec3f(buffer.data[pixel_sample.pixel_idx] * (iterations - 1)) +
                        integrators_[globals.integrator_id]->GetPixelColor(
                            ray,
                            pixel_sample,
                            scene_manager,
                            globals)) * (1.0f / globals.samples);

                    // Random noise test
                    // pixel_color += (
                    //     embree::Vec3f(buffer.data[pixel_sample.pixel_idx] * (iterations - 1)) +
                    //     embree::Vec3f(
                    //         pixel_sample.sampler.Uniform1D(),
                    //         pixel_sample.sampler.Uniform1D(),
                    //         pixel_sample.sampler.Uniform1D()))
                    //     * (1.0f / globals.samples);
                }

                buffer.data[pixel_sample.pixel_idx] = pixel_color / iterations;
            }
        }
    });

    spdlog::info(
        "TracerRenderer::Trace() - "
        "Rendered iteration number " + std::to_string(iterations) + ".");
}
