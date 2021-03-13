#ifndef CLI_H
#define CLI_H

#include <string>

#include "camera/camera.h"
#include "object/buffer.h"
#include "renderer/renderer.h"
#include "scene/scenemanager.h"
#include "utility/render.h"

#include "context/context.h"


class ContextCLI : public Context
{
    public:
        ContextCLI();
        ContextCLI(
            CLIArgs cli_args);

        virtual bool Initialize() override;
        virtual bool Execute() override;

    private:
        Buffer buffer_;
        Camera camera_;
        TracerRenderer renderer_;
        SceneManager scene_manager_;
        RenderGlobals globals_;
};

#endif // CLI_H
