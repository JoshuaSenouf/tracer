#include "window.h"


Window::Window()
{
    
}


int Window::renderWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(renderWidth, renderHeight, "Tracer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    gladLoadGL();

    ImGui_ImplGlfwGL3_Init(window, true);

    tracerRenderer.initRender(renderWidth, renderHeight);
    renderCamera.setCamera(glm::vec2(renderWidth, renderHeight));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //--------------
        // GUI setting & callbacks
        //--------------
        setupGUI();

        ImGuiIO& io = ImGui::GetIO();
        ImVec2 currentMousePos = ImGui::GetMousePos();

        keyboardCallback(&io);

        if (lastPosX !=  currentMousePos.x || lastPosY != currentMousePos.y)
            mouseCallback(&io, currentMousePos.x, currentMousePos.y);

        //--------------
        // CPU Rendering
        //--------------
        if (renderReset) // If anything in camera or scene data has changed, we flush the data and reinit them again
            resetRenderer();

        frameCounter++;

        tracerRenderer.renderTracer(renderWidth, renderHeight, renderSamples, renderBounces); // Progressive rendering
        tracerRenderer.displayGLBuffer();

        //----------------
        // GUI rendering
        //----------------
        renderGUI();

        glfwSwapBuffers(window);
    }

    //---------
    // Cleaning
    //---------
    stopGUI();

    glfwTerminate();

    return 0;
}


void Window::resetRenderer()
{
    frameCounter = 0;
    // RESET CODE

    renderReset = false;
}


void Window::aboutWindow(bool* guiOpen)
{
    ImGui::Begin("About", guiOpen);

    ImGui::Text("Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf");

    ImGui::End();
}


void Window::renderConfigWindow(bool* guiOpen)
{
    ImGui::Begin("Render Config", guiOpen);

    ImGui::InputInt("Width", &renderWidth);
    ImGui::InputInt("Height", &renderHeight);
    ImGui::InputInt("Samples", &renderSamples);
    ImGui::InputInt("Bounces", &renderBounces);

    ImGui::End();
}


void Window::setupGUI()
{
    ImGui_ImplGlfwGL3_NewFrame();

    if (aboutBool) aboutWindow(&aboutBool);
    if (renderBool) renderConfigWindow(&renderBool);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Rendering"))
        {
            if (ImGui::MenuItem("Render to PPM"))
            {
                tracerRenderer.renderToPPM(renderWidth, renderHeight, renderSamples, renderBounces);
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


void Window::renderGUI()
{
    ImGui::Render();
}


void Window::stopGUI()
{
    ImGui_ImplGlfwGL3_Shutdown();
}


void Window::keyboardCallback(ImGuiIO* guiIO)
{
    if (guiIO->KeysDown[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (guiIO->KeysDown[GLFW_KEY_W])
    {
        renderCamera.keyboardCall(FORWARD, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_S])
    {
        renderCamera.keyboardCall(BACKWARD, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_A])
    {
        renderCamera.keyboardCall(LEFT, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_D])
    {
        renderCamera.keyboardCall(RIGHT, deltaTime);
        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_KP_ADD])
    {
        if (guiIO->KeysDown[GLFW_KEY_LEFT_CONTROL])
            renderCamera.setCameraFocalDistance(renderCamera.getCameraFocalDistance() + 0.1f);
        else
            renderCamera.setCameraApertureRadius(renderCamera.getCameraApertureRadius() + 0.005f);

        renderReset = true;
    }

    if (guiIO->KeysDown[GLFW_KEY_KP_SUBTRACT])
    {
        if (guiIO->KeysDown[GLFW_KEY_LEFT_CONTROL])
            renderCamera.setCameraFocalDistance(renderCamera.getCameraFocalDistance() - 0.1f);
        else
            renderCamera.setCameraApertureRadius(renderCamera.getCameraApertureRadius() - 0.005f);

        renderReset = true;
    }
}


void Window::mouseCallback(ImGuiIO* guiIO, float mousePosX, float mousePosY)
{
    if (firstMouse)
    {
        lastPosX = mousePosX;
        lastPosY = mousePosY;
        firstMouse = false;
    }

    float offsetX = mousePosX - lastPosX;
    float offsetY = mousePosY - lastPosY;

    lastPosX = mousePosX;
    lastPosY = mousePosY;

    if (guiIO->MouseDown[GLFW_MOUSE_BUTTON_RIGHT])
    {
        if (offsetX != 0 || offsetY != 0)
        {
            renderCamera.mouseCall(offsetX, offsetY, true);
            renderReset = true;
        }
    }
}
