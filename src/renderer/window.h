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

        void renderConfigWindow(bool &guiOpen);
        void fpsWindow(bool& guiOpen);
        void aboutWindow(bool &guiOpen);

        void keyboardCallback(ImGuiIO &guiIO);
        void mouseCallback(ImGuiIO &guiIO, float mousePosX, float mousePosY);

    private:
        bool firstMouse = true;
        bool guiIsOpen = true;
        bool renderReset = false;
        bool renderConfigBool = false;
        bool fpsBool = true;
        bool aboutBool = false;
        bool pauseBool = false;
        bool swapBool = false;

        int frameCounter = 0;

        int progressiveWidth = 800;
        int progressiveHeight = 600;
        int progressiveSamples = 1;
        int progressiveBounces = 4;
        int outputWidth = 800;
        int outputHeight = 600;
        int outputSamples = 32;
        int outputBounces = 4;

        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        GLfloat lastPosX = progressiveWidth / 2.0f;
        GLfloat lastPosY = progressiveHeight / 2.0f;

        GLFWwindow* window;

        Camera renderCamera;
        CameraInfo renderCameraInfo;

        Renderer tracerRenderer;

        std::vector<Vector3> tempBuffer;
};


#endif // WINDOW_H
