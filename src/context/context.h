#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>

#include <spdlog/spdlog.h>

#include "buffer.h"
#include "camera.h"
#include "renderer.h"
#include "scenemanager.h"

#include "cli_helper.h"
#include "embree_helper.h"
#include "output_helper.h"
#include "render_helper.h"


struct Context
{
    Context();

    virtual bool Initialize() = 0;
    virtual bool Execute() = 0;

    CLIArgs _args;
};

#endif // CONTEXT_H
