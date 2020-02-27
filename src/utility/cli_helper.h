#ifndef CLI_HELPER_H
#define CLI_HELPER_H

#include <string>

#include "render_helper.h"


static const std::vector<std::string> modes {
    "cli",
    "gui"
};

struct CLIArgs
{
    std::string mode = "cli";
    std::string input;
    std::string output;
    RenderGlobals globals;
    int verbosity = 4;
};

#endif // CLI_HELPER_H
