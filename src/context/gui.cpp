#include "gui.h"


ContextGUI::ContextGUI()
{
    spdlog::trace("ContextGUI::ContextGUI()");
}

ContextGUI::ContextGUI(CLIArgs cliArgs)
{
    spdlog::trace("ContextGUI::ContextGUI(cliArgs)");

    _args = cliArgs;
}

bool ContextGUI::Initialize()
{
    spdlog::trace("ContextGUI::Initialize()");

    // Check if the user provided an existing input file on disk.
    if (!_args.input.empty() && !std::ifstream(_args.input))
    {
        spdlog::error("ContextGUI::Initialize() - "
            "The provided USD scene file does not exist on disk.");

        return 0;
    }

    _globals = _args.globals;

    spdlog::info("ContextGUI::Initialize() - "
        "Context has been initialized properly.");

    return true;
}

bool ContextGUI::Execute()
{
    spdlog::trace("ContextGUI::Execute()"); 

    return true;
}
