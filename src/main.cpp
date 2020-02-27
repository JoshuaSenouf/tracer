// Tracer by Joshua Senouf - 2017-2020

#include <CLI11.hpp>
#include <spdlog/spdlog.h>

#include "cli.h"
#include "cli_helper.h"
#include "gui.h"


int main(int argc, char** argv)
{
    spdlog::trace("main()");

    CLIArgs args;
    CLI::App cli{"Tracer CLI"};

    // Adding the excepted options to the argument parser.
    cli.add_option("--mode", args.mode, "Mode, i.e. \"cli\" or \"gui\". Default is \"cli\"");
    cli.add_option("--input", args.input, "Input USD scene to render");
    cli.add_option("--output", args.output, "Output path of rendered image, as an EXR file");
    cli.add_option("--width", args.globals.width, "Width of the render. Default is \"800\"");
    cli.add_option("--height", args.globals.height, "Height of the render. Default is \"600\"");
    cli.add_option("--samples", args.globals.samples, "Number of samples per pixels. Default is \"1\"");
    cli.add_option("--depth", args.globals.depth, "Maximum ray depth. Default is \"3\"");
    cli.add_option("--verbosity", args.verbosity, "Setup the verbosity level of the logger. "
        "The options are the following --> Trace:0|Debug:1|Info:2|Warning:3|Error:4|Critical:5|Off:6. "
        "Default is \"4\"");

    // Run the argument parsing.
    CLI11_PARSE(cli, argc, argv);

    spdlog::info("main() - "
        "Command line arguments parsed successfully.");

    // Set verbosity level of the logger.
    spdlog::set_level(static_cast<spdlog::level::level_enum>(args.verbosity));

    // Check if the user provided an existing mode.
    if (std::find(std::begin(modes), std::end(modes), args.mode) == modes.end())
    {
        spdlog::error("main() - "
            "The provided mode is unknown. The only available mode are \"cli\" and \"gui\".");

        return 0;
    }

    // Use a different context depending on the mode we are using.
    if (args.mode == "cli")
    {
        ContextCLI contextCLI(args);

        if(!contextCLI.Initialize())
        {
            return 0;
        }

        contextCLI.Execute();
    }
    else
    {
        ContextGUI contextGUI(args);

        if(!contextGUI.Initialize())
        {
            return 0;
        }

        contextGUI.Execute();
    }

    spdlog::info("main() - "
        "No error detected. Exiting Tracer...");

    return 1;
}