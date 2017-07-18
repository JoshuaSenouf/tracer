#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <fstream>
#include <vector>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>


class GUI
{
    public:
        GUI();

        void setupGUI();
        void renderGUI();
        void stopGUI();
        void setRenderResolution(int width, int height);
        void aboutWindow(bool* guiOpen);
        void renderConfigWindow(bool* guiOpen);

    private:
        bool aboutBool = false;
        bool renderBool = false;

        int renderWidth = 800;
        int renderHeight = 600;
        int renderSamples = 128;
        int renderBounces = 4;
};

#endif // GUI_H
