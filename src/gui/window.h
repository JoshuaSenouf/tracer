#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include <embree3/common/math/vec2.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include "buffer.h"
#include "camera.h"
#include "render_helper.h"
#include "rendermanager.h"
#include "scenemanager.h"


class Window
{
    public:
        Window();

        int RenderWindow();
        void ResetRenderer();
        void SetupGUI();
        void RenderGUI();
        void StopGUI();
        void RenderConfigWindow(bool &guiOpen);
        void ProfilingWindow(bool& guiOpen);
        void AboutWindow(bool &guiOpen);
        void KeyboardCallback(ImGuiIO &guiIO);
        void MouseCallback(ImGuiIO &guiIO,
            embree::Vec2fa mousePos);

    private:
        bool firstMouse = true;
        bool renderReset = false;
        bool renderConfigState = false;
        bool profilingState = true;
        bool aboutState = false;
        bool pauseState = false;
        bool swapState = false;
        int iterations = 0;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        embree::Vec2fa prevMousePos = embree::Vec2fa(globals.width / 2.0f, globals.height / 2.0f);

        Buffer frontBuffer;
        Buffer backBuffer;
        Camera camera;
        GLFWwindow* window;
        SceneManager scene;
        RenderManager renderManager;
        RenderGlobals globals;
};


#endif // WINDOW_H
