#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

        void aboutWindow(bool* guiOpen);
        void renderConfigWindow(bool* guiOpen);

        void keyboardCallback(ImGuiIO* guiIO);
        void mouseCallback(ImGuiIO* guiIO, float mousePosX, float mousePosY);

    private:
        bool firstMouse = true;
        bool guiIsOpen = true;
        bool renderReset = false;
        bool aboutBool = false;
        bool renderBool = false;

        int frameCounter = 0;

        int progressiveWidth = 800;
        int progressiveHeight = 600;
        int progressiveSamples = 1;
        int progressiveBounces = 4;
        int ppmWidth = 800;
        int ppmHeight = 600;
        int ppmSamples = 16;
        int ppmBounces = 4;

        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        GLfloat lastPosX = progressiveWidth / 2;
        GLfloat lastPosY = progressiveHeight / 2;

        GLFWwindow* window;

        Camera renderCamera;
        CameraInfo* renderCameraInfo;

        Renderer tracerRenderer;
};


#endif // WINDOW_H
