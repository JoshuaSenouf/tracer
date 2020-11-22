#include <chrono>

#include <spdlog/spdlog.h>

#include "context/cli.h"


ContextCLI::ContextCLI()
{
    spdlog::trace("ContextCLI::ContextCLI()");
}

ContextCLI::ContextCLI(
    CLIArgs cli_args)
{
    spdlog::trace("ContextCLI::ContextCLI(cli_args)");

    args_ = cli_args;
}

bool ContextCLI::Initialize()
{
    spdlog::trace("ContextCLI::Initialize()");

    // Check if the user provided an input USD scene file.
    if (args_.input.empty())
    {
        spdlog::error(
            "ContextCLI::Initialize() - "
            "No input USD scene file was provided.");

        return false;
    }

    // Check if the provided input USD scene file exists on disk.
    if (!std::ifstream(args_.input))
    {
        spdlog::error(
            "ContextCLI::Initialize() - "
            "The provided USD scene file does not exist on disk.");

        return false;
    }

    // Check if the user provided an output path.
    if (args_.output.empty())
    {
        spdlog::error(
            "ContextCLI::Initialize() - "
            "It is necessary to provide an output path when using the CLI mode.");

        return false;
    }

    globals_ = args_.globals;

    spdlog::debug(
        "ContextCLI::Initialize() - "
        "Context has been initialized properly.");

    return true;
}

bool ContextCLI::Execute()
{
    spdlog::trace("ContextCLI::Execute()");

    auto scene_start_time = std::chrono::high_resolution_clock::now();

    // Initializing the necessary data for the renderer_.
    scene_manager_.LoadScene(args_.input);

    auto scene_end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> scene_time = scene_end_time - scene_start_time;

    spdlog::info(
        "ContextCLI::Execute() - "
        "Scene loaded successfully in " + std::to_string(scene_time.count()) + " seconds.");

    camera_.Initialize(globals_.width, globals_.height);
    buffer_.Initialize(globals_.width, globals_.height);

    spdlog::info(
        "ContextCLI::Execute() - "
        "Rendering the scene...");

    auto render_start_time = std::chrono::high_resolution_clock::now();

    // Rendering the image as a single iteration.
    renderer_.Trace(
        globals_,
        scene_manager_,
        camera_,
        buffer_,
        1);

    auto render_end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> render_time = render_end_time - render_start_time;

    spdlog::info(
        "ContextCLI::Execute() - "
        "Scene rendered successfully in " + std::to_string(render_time.count()) + " seconds.");

    if (args_.format == "exr")
    {
        buffer_.ToEXR(
            args_.output);
    }
    else
    {
        buffer_.ToPPM(
            args_.output);
    }

    return true;
}
