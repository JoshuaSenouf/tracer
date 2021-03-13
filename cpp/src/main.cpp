// Tracer by Joshua Senouf - 2017-2021

// #define TINYEXR_IMPLEMENTATION

#include <CLI11.hpp>
#include <spdlog/spdlog.h>

#include "context/cli.h"
// #include "context/imgui.h"
// #include "context/qt.h"
#include "utility/cli.h"


int main(int argc, char** argv)
{
    spdlog::trace("main()");

    CLIArgs args;
    CLI::App cli{"Tracer CLI"};

    // Adding the excepted options to the argument parser.
    cli.add_option("--mode", args.mode, "Mode, i.e. \"cli\", \"imgui\" or \"qt\". Default is \"cli\"");
    cli.add_option("--input", args.input, "Input USD scene to render");
    cli.add_option("--output", args.output, "Output path of rendered image");
    cli.add_option("--format", args.format, "Image format used to store the rendered image. "
        "The options are the following --> PPM:ppm|EXR:exr. Default is \"exr\".");
    cli.add_option("--width", args.globals.width, "Width of the render. Default is \"800\"");
    cli.add_option("--height", args.globals.height, "Height of the render. Default is \"600\"");
    cli.add_option("--samples", args.globals.samples, "Number of samples per pixels. Default is \"1\"");
    cli.add_option("--depth", args.globals.depth, "Maximum ray depth. Default is \"3\"");
    cli.add_option("--verbosity", args.verbosity, "Setup the verbosity level of the logger. "
        "The options are the following --> Trace:0|Debug:1|Info:2|Warning:3|Error:4|Critical:5|Off:6. "
        "Default is \"4\"");

    // Run the argument parsing.
    CLI11_PARSE(cli, argc, argv);

    args.argc = argc;
    args.argv = argv;

    // Set verbosity level of the logger.
    spdlog::set_level(static_cast<spdlog::level::level_enum>(args.verbosity));

    spdlog::debug("main() - "
        "Command line arguments parsed successfully.");

    // Check if the user provided an existing mode.
    if (std::find(std::begin(kContextModes), std::end(kContextModes), args.mode) == kContextModes.end())
    {
        spdlog::error("main() - "
            "The provided mode is unknown. The only available mode are \"cli\" and \"gui\".");

        return 0;
    }

    // Use a different context depending on the mode we are using.
    if (args.mode == "cli")
    {
        ContextCLI context_cli(args);

        if(!context_cli.Initialize())
        {
            return 0;
        }

        context_cli.Execute();
    }
    // // else if (args.mode == "imgui")
    // // {
    // //     ContextImGUI context_imgui(args);

    // //     if(!context_imgui.Initialize())
    // //     {
    // //         return 0;
    // //     }

    // //     context_imgui.Execute();
    // // }
    // // else
    // // {
    // //     ContextQt context_qt(args);

    // //     if(!context_qt.Initialize())
    // //     {
    // //         return 0;
    // //     }

    // //     context_qt.Execute();
    // // }

    spdlog::debug("main() - "
        "No error detected. Exiting Tracer...");

    return 1;
}