#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include "camera.h"
#include "buffer.h"
#include "scenemanager.h"
#include "rendermanager.h"
#include "embree_helper.h"
#include "render_helper.h"

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720


class Window
{
    public:
        Window();

        int renderWindow();
        void resetRenderer();
        void setupGUI();
        void renderGUI();
        void stopGUI();

        void renderConfigWindow(bool &guiOpen);
        void fpsWindow(bool& guiOpen);
        void aboutWindow(bool &guiOpen);

        void keyboardCallback(ImGuiIO &guiIO);
        void mouseCallback(ImGuiIO &guiIO,
            float mousePosX,
            float mousePosY);

    private:
        bool firstMouse = true;
        bool guiIsOpen = true;
        bool renderReset = false;

        bool renderConfigBool = false;
        bool fpsBool = true;
        bool aboutBool = false;
        bool pauseBool = false;
        bool swapBool = false;

        bool cameraJitter = true;

        int frame = 0;

        int width = DEFAULT_WIDTH;
        int height = DEFAULT_HEIGHT;
        int samples = 1;
        int depth = 4;
        int integratorID = DEBUG;

        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        GLfloat lastPosX = width / 2.0f;
        GLfloat lastPosY = height / 2.0f;

        GLFWwindow* window;

        Camera camera;
        RenderManager renderer;
        SceneManager scene;

        Buffer frontBuffer;
        Buffer backBuffer;
};


#endif // WINDOW_H
