#ifndef CLI_UTILITY_H
#define CLI_UTILITY_H

#include <string>

#include "utility/render.h"


static const std::vector<std::string> kContextModes {
    "cli",
    "gui",
    "imgui"
};

static const std::vector<std::string> kImageFormats {
    "ppm",
    "exr"
};

struct CLIArgs
{
    std::string mode = "imgui";
    std::string input;
    std::string output;
    std::string format = "ppm";
    RenderGlobals globals;
    int verbosity = 2;
    int argc;
    char **argv;
};

#endif // CLI_UTILITY_H
