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

#include "renderer.h"
#include "camera.h"


class Window
{
    public:
        Window();
        int renderWindow();
        void resetRenderer();
        void setupGUI();
        void renderGUI();
        void stopGUI();

        void aboutWindow(bool &guiOpen);
        void renderConfigWindow(bool &guiOpen);

        void keyboardCallback(ImGuiIO &guiIO);
        void mouseCallback(ImGuiIO &guiIO, float mousePosX, float mousePosY);

    private:
        bool firstMouse = true;
        bool guiIsOpen = true;
        bool renderReset = false;
        bool aboutBool = false;
        bool renderBool = false;
        bool pauseBool = false;
        bool swapBool = false;

        int frameCounter = 0;

        int progressiveWidth = 800;
        int progressiveHeight = 600;
        int progressiveSamples = 1;
        int progressiveBounces = 4;
        int ppmWidth = 800;
        int ppmHeight = 600;
        int ppmSamples = 32;
        int ppmBounces = 4;

        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        GLfloat lastPosX = progressiveWidth / 2.0f;
        GLfloat lastPosY = progressiveHeight / 2.0f;

        GLFWwindow* window;

        Camera renderCamera;
        CameraInfo renderCameraInfo;

        Renderer tracerRenderer;
};


#endif // WINDOW_H
