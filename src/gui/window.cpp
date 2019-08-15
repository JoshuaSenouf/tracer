#include "window.h"

#include "output_helper.h"


Window::Window()
{
}

int Window::RenderWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(globals.width, globals.height, "Tracer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    gladLoadGL();

    ImGui_ImplGlfwGL3_Init(window, true);

    scene.LoadScene("res/scenes/cupandsaucer.usdz");

    camera._resolution = embree::Vec2fa(globals.width, globals.height);
    camera.Init();

    frontBuffer.Init(globals.width, globals.height);
    backBuffer.Init(globals.width, globals.height);

    renderManager.SetupScreenQuad(globals.width, globals.height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //--------------
        // GUI setting & callbacks
        //--------------
        SetupGUI();
        ImGuiIO guiIO(ImGui::GetIO());

        KeyboardCallback(guiIO);

        // ImVec2 mousePos(ImGui::GetMousePos());
        embree::Vec2fa mousePos(ImGui::GetMousePos().x, ImGui::GetMousePos().y);

        if (prevMousePos.x != mousePos.x ||
            prevMousePos.y != mousePos.y)
        {
            MouseCallback(guiIO, mousePos);
        }

        // TODO: Will make use of Qt's callback system once the GUI will be revamped.
        if (camera._jitter != globals.rayJitter)
        {
            camera._jitter = globals.rayJitter;

            renderReset = true;
        }
        if (renderManager.integratorID != globals.integratorID)
        {
            renderManager.integratorID = globals.integratorID;

            renderReset = true;
        }

        //--------------
        // CPU Rendering
        //--------------
        if (!pauseState)
        {
            // If anything changed in the camera, scene, settings, etc, we flush the rendered data and reinit them again
            if (renderReset)
            {
                ResetRenderer();
            }

            iterations++;

            // Progressive rendering
            renderManager.Trace(globals,
                scene,
                camera,
                frontBuffer,
                iterations);
            renderManager.RenderToScreenTexture(globals.width,
                globals.height,
                frontBuffer);
        }

        renderManager.DrawScreenQuad();

        //----------------
        // GUI rendering
        //----------------
        RenderGUI();

        glfwSwapBuffers(window);
    }

    //---------
    // Cleaning
    //---------
    StopGUI();

    glfwTerminate();

    return 0;
}

void Window::ResetRenderer()
{
    frontBuffer.Clean(globals.width, globals.height);

    iterations = 0;
    renderReset = false;
}

void Window::SetupGUI()
{
    ImGui_ImplGlfwGL3_NewFrame();

    if (profilingState)
        ProfilingWindow(profilingState);
    if (aboutState)
        AboutWindow(aboutState);
    if (renderConfigState)
        RenderConfigWindow(renderConfigState);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Render to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    Buffer outputBuffer;
                    outputBuffer.Init(globals.width, globals.height);

                    renderManager.Trace(globals,
                        scene,
                        camera,
                        outputBuffer,
                        1);

                    toPPM(globals.width,
                        globals.height,
                        outputBuffer);
                }

                if (ImGui::MenuItem("EXR"))
                {
                    Buffer outputBuffer;
                    outputBuffer.Init(globals.width, globals.height);
                    
                    renderManager.Trace(globals,
                        scene,
                        camera,
                        outputBuffer,
                        1);

                    toEXR(globals.width,
                        globals.height,
                        outputBuffer);
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Export to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    toPPM(globals.width,
                        globals.height,
                        frontBuffer);
                }

                if (ImGui::MenuItem("EXR"))
                {
                    toEXR(globals.width,
                        globals.height,
                        frontBuffer);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Rendering"))
        {
            if (ImGui::BeginMenu("Integrator"))
            {
                ImGui::RadioButton("UDPT", &globals.integratorID, 0);
                ImGui::RadioButton("Diffuse", &globals.integratorID, 1);
                ImGui::RadioButton("Occlusion", &globals.integratorID, 2);
                ImGui::RadioButton("Position", &globals.integratorID, 3);
                ImGui::RadioButton("Normal", &globals.integratorID, 4);
                ImGui::RadioButton("Debug", &globals.integratorID, 5);

                ImGui::EndMenu();
            }
            
            ImGui::Separator();
            ImGui::MenuItem("Config", NULL, &renderConfigState);

            if (!swapState)
            {
                ImGui::Separator();
                ImGui::Checkbox("Pause Render", &pauseState);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Camera"))
        {
            ImGui::Checkbox("Jitter Rays", &globals.rayJitter);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::BeginMenu("Load..."))
            {
                if (ImGui::MenuItem("Cup and Saucer"))
                {
                    scene.LoadScene("res/scenes/usd/cupandsaucer.usdz");
                    camera.Init();

                    renderReset = true;
                }

                if (ImGui::MenuItem("Stormtroopers"))
                {
                    scene.LoadScene("res/scenes/usd/stormtroopers.usdc");
                    camera.Init();

                    renderReset = true;
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Profiling", NULL, &profilingState);
            ImGui::Separator();
            ImGui::MenuItem("About", NULL, &aboutState);

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Window::RenderGUI()
{
    ImGui::Render();
}

void Window::StopGUI()
{
    ImGui_ImplGlfwGL3_Shutdown();
}

void Window::RenderConfigWindow(bool& guiOpen)
{
    ImGui::Begin("Render Config", &guiOpen);

    ImGui::InputInt("Width", &globals.width);
    ImGui::InputInt("Height", &globals.height);
    ImGui::InputInt("Samples", &globals.samples);
    ImGui::InputInt("Depth", &globals.depth);

    ImGui::Separator();

    if (!swapState)
    {
        if (ImGui::Button("Save To Back Buffer"))
        {
            backBuffer.Clean(globals.width, globals.height);
            backBuffer._data = frontBuffer._data;
        }
    }
    if (ImGui::Button("Swap Buffers"))
    {
        frontBuffer.Swap(backBuffer);
        renderManager.RenderToScreenTexture(globals.width, globals.height, frontBuffer);

        swapState = !swapState;
        pauseState = true;
    }

    ImGui::End();
}

void Window::ProfilingWindow(bool& guiOpen)
{
    ImGui::Begin("Profiling",
        &guiOpen,
        ImGuiWindowFlags_NoTitleBar
        |ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Framerate: %.2f FPS / %.2f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", camera._position.x, camera._position.y, camera._position.z);

    ImGui::End();
}

void Window::AboutWindow(bool& guiOpen)
{
    ImGui::Begin("About", &guiOpen);

    ImGui::Text("Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf");

    ImGui::End();
}

void Window::KeyboardCallback(ImGuiIO& guiIO)
{
    if (guiIO.KeysDown[GLFW_KEY_ESCAPE])
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (guiIO.KeysDown[GLFW_KEY_W])
    {
        camera.KeyboardCallback(FORWARD, deltaTime);

        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_S])
    {
        camera.KeyboardCallback(BACKWARD, deltaTime);

        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_A])
    {
        camera.KeyboardCallback(LEFT, deltaTime);

        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_D])
    {
        camera.KeyboardCallback(RIGHT, deltaTime);

        renderReset = true;
    }

    if (guiIO.KeysDown[GLFW_KEY_KP_ADD])
    {
        if (guiIO.KeysDown[GLFW_KEY_LEFT_CONTROL])
        {
            camera._focalDistance = camera._focalDistance + 0.1f;
        }
        else
        {
            camera._apertureRadius = camera._apertureRadius + 0.005f;
        }

        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_KP_SUBTRACT])
    {
        if (guiIO.KeysDown[GLFW_KEY_LEFT_CONTROL])
        {
            camera._focalDistance = camera._focalDistance - 0.1f;
        }
        else
        {
            camera._apertureRadius = camera._apertureRadius - 0.005f;
        }

        renderReset = true;
    }
}

void Window::MouseCallback(ImGuiIO& guiIO,
    embree::Vec2fa mousePos)
{
    if (firstMouse)
    {
        prevMousePos = embree::Vec2fa(mousePos);

        firstMouse = false;
    }

    embree::Vec2fa mouseOffset(mousePos.x - prevMousePos.x,
        mousePos.y - prevMousePos.y);
    prevMousePos = embree::Vec2fa(mousePos);

    if (guiIO.MouseDown[GLFW_MOUSE_BUTTON_RIGHT])
    {
        if (mouseOffset != embree::Vec2fa())

        {
            camera.MouseCallback(mouseOffset);

            renderReset = true;
        }
    }
}
