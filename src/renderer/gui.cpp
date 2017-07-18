#include "gui.h"


GUI::GUI()
{
    
}


void GUI::setupGUI()
{
    ImGui_ImplGlfwGL3_NewFrame();

    if (aboutBool) aboutWindow(&aboutBool);
    if (renderBool) renderConfigWindow(&renderBool);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Rendering"))
        {
            if (ImGui::MenuItem("Save Render to PPM"))
            {

            }

            ImGui::Separator();

            ImGui::MenuItem("Config", NULL, &renderBool);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", NULL, &aboutBool);

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}


void GUI::renderGUI()
{
    ImGui::Render();
}


void GUI::stopGUI()
{
    ImGui_ImplGlfwGL3_Shutdown();
}


void GUI::setRenderResolution(int width, int height)
{
    renderWidth = width;
    renderHeight = height;
}


void GUI::aboutWindow(bool* guiOpen)
{
    ImGui::Begin("About", guiOpen);

    ImGui::Text("Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf");

    ImGui::End();
}


void GUI::renderConfigWindow(bool* guiOpen)
{
    ImGui::Begin("Render Config", guiOpen);

    ImGui::InputInt("Width", &renderWidth);
    ImGui::InputInt("Height", &renderHeight);
    ImGui::InputInt("Samples", &renderSamples);
    ImGui::InputInt("Bounces", &renderBounces);

    ImGui::End();
}
