#ifndef IMGUI_H
#define IMGUI_H

#include <string>

#include "camera/camera.h"
#include "object/buffer.h"
#include "renderer/renderer.h"
#include "scene/scenemanager.h"
#include "utility/render.h"

#include "gui/imgui/window.h"

#include "context/context.h"


class ContextImGUI : public Context
{
    public:
        ContextImGUI();
        ContextImGUI(
            CLIArgs cli_args);

        virtual bool Initialize() override;
        virtual bool Execute() override;

    private:
        Buffer buffer_;
        Camera camera_;
        TracerRenderer renderer_;
        SceneManager scene_manager_;
        RenderGlobals globals_;

        WindowImGui *window;
};

#endif // IMGUI_H
