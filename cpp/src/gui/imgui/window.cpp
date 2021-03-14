#include <spdlog/spdlog.h>

#include "utility/camera.h"
#include "utility/glfw.h"
#include "utility/opengl.h"

#include "gui/imgui/window.h"


WindowImGui::WindowImGui()
{
    spdlog::trace("WindowImGui::WindowImGui()");
}

int WindowImGui::RenderWindow()
{
    spdlog::trace("WindowImGui::RenderWindow()");

    glfwSetErrorCallback(GLFWErrorCallback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 450";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(globals.width, globals.height, "Tracer", nullptr, nullptr);
    if (window == nullptr)
    {
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool glad_error = gladLoadGL() == 0;
    if (glad_error)
    {
        spdlog::error(
            "WindowImGui::RenderWindow()"
            "Failed to initialize OpenGL loader!");

        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& gui_io = ImGui::GetIO(); (void)gui_io;
    ImGui::StyleColorsClassic();
    // ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    scene.LoadScene("resources/scenes/usd/cupandsaucer.usdz");
    camera.Initialize(globals.width, globals.height);
    buffer_front.Initialize(globals.width, globals.height);
    buffer_back.Initialize(globals.width, globals.height);

    SetupScreenQuad(globals.width, globals.height);

    while (!glfwWindowShouldClose(window))
    {
        float current_frame(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glfwPollEvents();

        //--------------
        // GUI setting & callbacks
        //--------------
        SetupGUI();

        KeyboardCallback(gui_io);

        // ImVec2 mouse_pos(ImGui::GetMousePos());
        embree::Vec2fa mouse_pos(ImGui::GetMousePos().x, ImGui::GetMousePos().y);

        if (previous_mouse_pos.x != mouse_pos.x ||
            previous_mouse_pos.y != mouse_pos.y)
        {
            MouseCallback(gui_io, mouse_pos);
        }

        if (camera.jitter_rays != globals.jitter_rays)
        {
            camera.jitter_rays = globals.jitter_rays;

            render_reset = true;
        }
        // if (renderManager.integrator_id != globals.integrator_id)
        // {
        //     renderManager.integrator_id = globals.integrator_id;

        //     render_reset = true;
        // }

        //--------------
        // CPU Rendering
        //--------------
        // if (!state_pause)
        // {
            // If anything changed in the camera, scene, settings, etc, we flush the rendered data and reinit them again
            // if (render_reset)
            // {
            //     ResetRenderer();
            // }

            // iterations++;

            // Progressive rendering
            // renderManager.Trace(globals,
            //     scene,
            //     camera,
            //     buffer_front,
            //     iterations);
            // renderManager.RenderToScreenTexture(globals.width,
            //     globals.height,
            //     buffer_front);
        // }

        // renderManager.DrawScreenQuad();
        RenderToScreenTexture(globals.width,
                globals.height,
                buffer_front);
        DrawScreenQuad();

        //----------------
        // GUI rendering
        //----------------
        RenderGUI();

        glfwGetFramebufferSize(window, &globals.width, &globals.height);
        glViewport(0, 0, globals.width, globals.height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    //---------
    // Cleaning
    //---------
    StopGUI();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void WindowImGui::ResetRenderer()
{
    spdlog::trace("WindowImGui::ResetRenderer()");

    buffer_front.Clean(globals.width, globals.height);

    iterations = 0;
    render_reset = false;
}

void WindowImGui::SetupGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (state_profiling)
        ProfilingWindow(state_profiling);
    if (state_about)
        AboutWindow(state_about);
    if (state_render_config)
        RenderConfigWindow(state_render_config);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Render to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    // Buffer outputBuffer;
                    // outputBuffer.Initialize(globals.width, globals.height);

                    // renderManager.Trace(globals,
                    //     scene,
                    //     camera,
                    //     outputBuffer,
                    //     1);

                    // outputBuffer.ToPPM(globals.width,
                    //     globals.height,
                    //     outputBuffer);
                }

                if (ImGui::MenuItem("EXR"))
                {
                    // Buffer outputBuffer;
                    // outputBuffer.Initialize(globals.width, globals.height);

                    // renderManager.Trace(globals,
                    //     scene,
                    //     camera,
                    //     outputBuffer,
                    //     1);

                    // outputBuffer.ToEXR(globals.width,
                    //     globals.height,
                    //     outputBuffer);
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Export to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    // outputBuffer.ToPPM(globals.width,
                    //     globals.height,
                    //     buffer_front);
                }

                if (ImGui::MenuItem("EXR"))
                {
                    // outputBuffer.ToEXR(globals.width,
                    //     globals.height,
                    //     buffer_front);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Rendering"))
        {
            if (ImGui::BeginMenu("Integrator"))
            {
                ImGui::RadioButton("UDPT", &globals.integrator_id, 0);
                ImGui::RadioButton("Diffuse", &globals.integrator_id, 1);
                ImGui::RadioButton("Occlusion", &globals.integrator_id, 2);
                ImGui::RadioButton("Position", &globals.integrator_id, 3);
                ImGui::RadioButton("Normal", &globals.integrator_id, 4);
                ImGui::RadioButton("Debug", &globals.integrator_id, 5);

                ImGui::EndMenu();
            }

            ImGui::Separator();
            ImGui::MenuItem("Config", NULL, &state_render_config);

            if (!state_swap)
            {
                ImGui::Separator();
                ImGui::Checkbox("Pause Render", &state_pause);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Camera"))
        {
            ImGui::Checkbox("Jitter Rays", &globals.jitter_rays);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::BeginMenu("Load..."))
            {
                if (ImGui::MenuItem("Cup and Saucer"))
                {
                    // scene.LoadScene("resources/scenes/usd/cupandsaucer.usdz");
                    // camera.Initialize(globals.width, globals.height);

                    render_reset = true;
                }

                if (ImGui::MenuItem("Stormtroopers"))
                {
                    // scene.LoadScene("resources/scenes/usd/stormtroopers.usdc");
                    // camera.Initialize(globals.width, globals.height);

                    // render_reset = true;
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Profiling", NULL, &state_profiling);
            ImGui::Separator();
            ImGui::MenuItem("About", NULL, &state_about);

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void WindowImGui::RenderGUI()
{
    ImGui::Render();
}

void WindowImGui::StopGUI()
{
    spdlog::trace("WindowImGui::StopGUI()");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void WindowImGui::RenderConfigWindow(bool& gui_open)
{
    ImGui::Begin("Render Config", &gui_open);

    ImGui::InputInt("Width", &globals.width);
    ImGui::InputInt("Height", &globals.height);
    ImGui::InputInt("Samples", &globals.samples);
    ImGui::InputInt("Depth", &globals.depth);

    ImGui::Separator();

    if (!state_swap)
    {
        if (ImGui::Button("Save To Back Buffer"))
        {
            // buffer_back.Clean(globals.width, globals.height);
            // buffer_back.data = buffer_front.data;
        }
    }
    if (ImGui::Button("Swap Buffers"))
    {
        // buffer_front.Swap(buffer_back);
        // renderManager.RenderToScreenTexture(globals.width, globals.height, buffer_front);

        state_swap = !state_swap;
        state_pause = true;
    }

    ImGui::End();
}

void WindowImGui::ProfilingWindow(bool& gui_open)
{
    ImGui::Begin("Profiling",
        &gui_open,
        ImGuiWindowFlags_NoTitleBar
        |ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Framerate: %.2f FPS / %.2f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", camera.position.x, camera.position.y, camera.position.z);

    ImGui::End();
}

void WindowImGui::AboutWindow(bool& gui_open)
{
    ImGui::Begin("About", &gui_open);

    ImGui::Text("Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf");

    ImGui::End();
}

void WindowImGui::KeyboardCallback(ImGuiIO& gui_io)
{
    if (gui_io.KeysDown[GLFW_KEY_ESCAPE])
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (gui_io.KeysDown[GLFW_KEY_W])
    {
        // camera.KeyboardCallback(kForward, delta_time);

        render_reset = true;
    }
    if (gui_io.KeysDown[GLFW_KEY_S])
    {
        // camera.KeyboardCallback(kBackward, delta_time);

        render_reset = true;
    }
    if (gui_io.KeysDown[GLFW_KEY_A])
    {
        // camera.KeyboardCallback(kLeft, delta_time);

        render_reset = true;
    }
    if (gui_io.KeysDown[GLFW_KEY_D])
    {
        // camera.KeyboardCallback(kRight, delta_time);

        render_reset = true;
    }

    if (gui_io.KeysDown[GLFW_KEY_KP_ADD])
    {
        if (gui_io.KeysDown[GLFW_KEY_LEFT_CONTROL])
        {
            // camera.focal_distance = camera.focal_distance + 0.1f;
        }
        else
        {
            // camera.aperture_radius = camera.aperture_radius + 0.005f;
        }

        render_reset = true;
    }
    if (gui_io.KeysDown[GLFW_KEY_KP_SUBTRACT])
    {
        if (gui_io.KeysDown[GLFW_KEY_LEFT_CONTROL])
        {
            // camera.focal_distance = camera.focal_distance - 0.1f;
        }
        else
        {
            // camera.aperture_radius = camera.aperture_radius - 0.005f;
        }

        render_reset = true;
    }
}

void WindowImGui::MouseCallback(ImGuiIO& gui_io,
    embree::Vec2fa mouse_pos)
{
    if (first_mouse)
    {
        previous_mouse_pos = embree::Vec2fa(mouse_pos);

        first_mouse = false;
    }

    embree::Vec2fa mouseOffset(mouse_pos.x - previous_mouse_pos.x,
        mouse_pos.y - previous_mouse_pos.y);
    previous_mouse_pos = embree::Vec2fa(mouse_pos);

    if (gui_io.MouseDown[GLFW_MOUSE_BUTTON_RIGHT])
    {
        if (mouseOffset != embree::Vec2fa())

        {
            // camera.MouseCallback(mouseOffset);

            render_reset = true;
        }
    }
}

void WindowImGui::RenderToScreenTexture(int width,
    int height,
    Buffer& buffer)
{
    glBindTexture(GL_TEXTURE_2D, screen_texture_id);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, buffer.data.data());
    screen_quad_shader.Use();
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, screen_texture_id);
}

void WindowImGui::SetupScreenQuad(int width,
    int height)
{
    spdlog::trace("WindowImGui::SetupScreenQuad()");

    // Screen quad geometry.
    glGenVertexArrays(1, &screen_quad_vao);
    glGenBuffers(1, &screen_quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, screen_quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen_quad_vertices), screen_quad_vertices, GL_STATIC_DRAW);

    glBindVertexArray(screen_quad_vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    // Screen quad shader and texture.
    screen_quad_shader.Setup("resources/shaders/glsl/screen_quad.vert",
        "resources/shaders/glsl/screen_quad.frag");

    glGenTextures(1, &screen_texture_id);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, screen_texture_id);

    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width, height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void WindowImGui::CleanScreenQuad()
{
    spdlog::trace("WindowImGui::CleanScreenQuad()");

    glBindBuffer(GL_ARRAY_BUFFER, screen_quad_vbo);
    glDeleteBuffers(1, &screen_quad_vbo);

    screen_quad_vbo = 0;
}

void WindowImGui::DrawScreenQuad()
{
    glBindVertexArray(screen_quad_vao);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}
