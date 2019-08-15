#include "cli.h"


ContextCLI::ContextCLI()
{
    spdlog::trace("ContextCLI::ContextCLI()");
}

ContextCLI::ContextCLI(CLIArgs cliArgs)
{
    spdlog::trace("ContextCLI::ContextCLI(cliArgs)");

    _args = cliArgs;
}

bool ContextCLI::Initialize()
{
    spdlog::trace("ContextCLI::Initialize()");

    // Check if the user provided an input USD scene file.
    if (_args.input.empty())
    {
        spdlog::error("ContextCLI::Initialize() - "
            "No input USD scene file was provided.");

        return 0;
    }

    // Check if the provided input USD scene file exists on disk.
    if (!std::ifstream(_args.input))
    {
        spdlog::error("ContextCLI::Initialize() - "
            "The provided USD scene file does not exist on disk.");

        return 0;
    }

    // Check if the user provided an output path.
    if (_args.output.empty())
    {
        spdlog::error("ContextCLI::Initialize() - "
            "It is necessary to provide an output path when using the CLI mode.");

        return false;
    }

    _globals = _args.globals;

    spdlog::info("ContextCLI::Initialize() - "
        "Context has been initialized properly.");

    return true;
}

bool ContextCLI::Execute()
{
    spdlog::trace("ContextCLI::Execute()");

    // Initializing the necessary data for the renderer.
    _scene.LoadScene(_args.input);
    _camera.Init(_globals.width, _globals.height);
    _outputBuffer.Init(_globals.width, _globals.height);

    spdlog::info("ContextCLI::Execute() - "
        "Rendering the scene...");

    // Rendering the image as a single iteration.
    _renderer.Trace(_globals,
        _scene,
        _camera,
        _outputBuffer,
        1);

    spdlog::info("ContextCLI::Execute() - "
        "Scene rendered successfully.");

    // Exporting the result as an EXR image file.
    toEXR(_globals.width,
        _globals.height,
        _outputBuffer);

    spdlog::info("ContextCLI::Execute() - "
        "Context task finished.");

    return true;
}
