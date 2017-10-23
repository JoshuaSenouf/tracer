#include "window.h"


Window::Window()
{
    
}


int Window::renderWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(progressiveWidth, progressiveHeight, "Tracer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    gladLoadGL();

    ImGui_ImplGlfwGL3_Init(window, true);

    renderScene.loadSceneFile("res/scenes/materialTest.xml");

    tracerRenderer.initRender(progressiveWidth, progressiveHeight);
    renderCamera.setCamera(Vector2(progressiveWidth, progressiveHeight));

    frontBuffer.initBuffer(progressiveWidth, progressiveHeight);
    backBuffer.initBuffer(progressiveWidth, progressiveHeight);

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
        ImGuiIO guiIO = ImGui::GetIO();

        keyboardCallback(guiIO);

        ImVec2 currentMousePos = ImGui::GetMousePos();

        if (lastPosX != currentMousePos.x || lastPosY != currentMousePos.y)
            mouseCallback(guiIO, currentMousePos.x, currentMousePos.y);

        //--------------
        // CPU Rendering
        //--------------
        if (!pauseBool)
        {
            if (renderReset) // If anything in camera or scene data has changed, we flush the data and reinit them again
                resetRenderer();

            frameCounter++;

            tracerRenderer.traceLoop(progressiveWidth, progressiveHeight, progressiveSamples, progressiveBounces, frameCounter, frontBuffer.getBufferData()); // Progressive rendering
            tracerRenderer.renderToTexture(progressiveWidth, progressiveHeight, frontBuffer.getBufferData());
        }

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
    frontBuffer.cleanBufferData(progressiveWidth, progressiveHeight);

    renderReset = false;
}


void Window::fpsWindow(bool& guiOpen)
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 160, 30), 1);

    ImGui::Begin("FPS Counter", &guiOpen, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("Framerate %.2f FPS", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

    ImGui::End();
}


void Window::aboutWindow(bool& guiOpen)
{
    ImGui::Begin("About", &guiOpen);

    ImGui::Text("Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf");

    ImGui::End();
}


void Window::renderConfigWindow(bool& guiOpen)
{
    ImGui::Begin("Render Config", &guiOpen);

    ImGui::Text("Progressive configuration");
    ImGui::InputInt("Progressive Width", &progressiveWidth);
    ImGui::InputInt("Progressive Height", &progressiveHeight);
    ImGui::InputInt("Progressive Samples", &progressiveSamples);
    ImGui::InputInt("Progressive Bounces", &progressiveBounces);

    if (!swapBool)
    {
        if (ImGui::Button("Save To Back Buffer"))
        {
            backBuffer.cleanBufferData(progressiveWidth, progressiveHeight);
            backBuffer.setBufferData(frontBuffer.getBufferData());
        }
    }

    if (ImGui::Button("Swap Buffers"))
    {
        frontBuffer.swapBufferData(backBuffer.getBufferData());
        tracerRenderer.renderToTexture(progressiveWidth, progressiveHeight, frontBuffer.getBufferData());

        swapBool = !swapBool;

        if (swapBool)
            pauseBool = true;
        else
            pauseBool = false;
    }

    ImGui::Separator();

    ImGui::Text("Output configuration");
    ImGui::InputInt("Output Width", &outputWidth);
    ImGui::InputInt("Output Height", &outputHeight);
    ImGui::InputInt("Output Samples", &outputSamples);
    ImGui::InputInt("Output Bounces", &outputBounces);

    ImGui::End();
}


void Window::setupGUI()
{
    ImGui_ImplGlfwGL3_NewFrame();

    if (fpsBool)
        fpsWindow(fpsBool);
    if (aboutBool)
        aboutWindow(aboutBool);
    if (renderConfigBool)
        renderConfigWindow(renderConfigBool);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Rendering"))
        {
            if (ImGui::BeginMenu("Render to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    std::vector<Vector3> ppmBuffer;

                    ppmBuffer.resize(outputWidth * outputHeight);
                    tracerRenderer.traceLoop(outputWidth, outputHeight, outputSamples, outputBounces, 1, ppmBuffer);

                    exportToPPM(outputWidth, outputHeight, ppmBuffer);
                }

                if (ImGui::MenuItem("EXR"))
                {
                    std::vector<Vector3> exrBuffer;

                    exrBuffer.resize(outputWidth * outputHeight);
                    tracerRenderer.traceLoop(outputWidth, outputHeight, outputSamples, outputBounces, 1, exrBuffer);

                    exportToEXR(outputWidth, outputHeight, exrBuffer);
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Export to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    exportToPPM(outputWidth, outputHeight, frontBuffer.getBufferData());
                }

                if (ImGui::MenuItem("EXR"))
                {
                    exportToEXR(outputWidth, outputHeight, frontBuffer.getBufferData());
                }

                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (!swapBool)
            {
                ImGui::Checkbox("Pause Render", &pauseBool);

                ImGui::Separator();
            }

            ImGui::MenuItem("Config", NULL, &renderConfigBool);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::BeginMenu("Load..."))
            {
                if (ImGui::MenuItem("Cornell Box"))
                {
                    renderScene.loadSceneFile("res/scenes/cornell.xml");
                    renderReset = true;
                }

                if (ImGui::MenuItem("Material Test"))
                {
                    renderScene.loadSceneFile("res/scenes/materialTest.xml");
                    renderReset = true;
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Profiling", NULL, &fpsBool);

            ImGui::Separator();

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


void Window::keyboardCallback(ImGuiIO& guiIO)
{
    if (guiIO.KeysDown[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (guiIO.KeysDown[GLFW_KEY_W])
    {
        renderCamera.keyboardCall(FORWARD, deltaTime);
        renderReset = true;
    }

    if (guiIO.KeysDown[GLFW_KEY_S])
    {
        renderCamera.keyboardCall(BACKWARD, deltaTime);
        renderReset = true;
    }

    if (guiIO.KeysDown[GLFW_KEY_A])
    {
        renderCamera.keyboardCall(LEFT, deltaTime);
        renderReset = true;
    }

    if (guiIO.KeysDown[GLFW_KEY_D])
    {
        renderCamera.keyboardCall(RIGHT, deltaTime);
        renderReset = true;
    }

    if (guiIO.KeysDown[GLFW_KEY_KP_ADD])
    {
        if (guiIO.KeysDown[GLFW_KEY_LEFT_CONTROL])
            renderCamera.setCameraFocalDistance(renderCamera.getCameraFocalDistance() + 0.1f);
        else
            renderCamera.setCameraApertureRadius(renderCamera.getCameraApertureRadius() + 0.005f);

        renderReset = true;
    }

    if (guiIO.KeysDown[GLFW_KEY_KP_SUBTRACT])
    {
        if (guiIO.KeysDown[GLFW_KEY_LEFT_CONTROL])
            renderCamera.setCameraFocalDistance(renderCamera.getCameraFocalDistance() - 0.1f);
        else
            renderCamera.setCameraApertureRadius(renderCamera.getCameraApertureRadius() - 0.005f);

        renderReset = true;
    }
}


void Window::mouseCallback(ImGuiIO& guiIO, float mousePosX, float mousePosY)
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

    if (guiIO.MouseDown[GLFW_MOUSE_BUTTON_RIGHT])
    {
        if (offsetX != 0 || offsetY != 0)
        {
            renderCamera.mouseCall(offsetX, offsetY, true);
            renderReset = true;
        }
    }
}
