#ifndef WINDOWIMGUI_H
#define WINDOWIMGUI_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include <embree3/common/math/vec2.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "camera/camera.h"
#include "opengl/glshader.h"
#include "object/buffer.h"
#include "scene/scenemanager.h"
#include "utility/render.h"
#include "renderer/renderer.h"


class WindowImGui
{
    public:
        WindowImGui();

        int RenderWindow();
        void ResetRenderer();
        void SetupGUI();
        void RenderGUI();
        void StopGUI();
        void RenderConfigWindow(bool &gui_open);
        void ProfilingWindow(bool& gui_open);
        void AboutWindow(bool &gui_open);
        void KeyboardCallback(ImGuiIO &gui_io);
        void MouseCallback(ImGuiIO &gui_io,
            embree::Vec2fa mouse_pos);

        void RenderToScreenTexture(int width,
            int height,
            Buffer& buffer);
        void SetupScreenQuad(int width,
            int height);
        void CleanScreenQuad();
        void DrawScreenQuad();
    private:
        bool first_mouse = true;
        bool render_reset = false;
        bool state_render_config = false;
        bool state_profiling = true;
        bool state_about = false;
        bool state_pause = false;
        bool state_swap = false;
        int iterations = 0;
        float delta_time = 0.0f;
        float last_frame = 0.0f;
        embree::Vec2fa previous_mouse_pos = embree::Vec2fa(globals.width / 2.0f, globals.height / 2.0f);

        Buffer buffer_front;
        Buffer buffer_back;
        Camera camera;
        GLFWwindow* window;
        SceneManager scene;
        RenderGlobals globals;
        TracerRenderer renderer;

        GLuint screen_quad_vao;
        GLuint screen_quad_vbo;
        GLuint screen_texture_id;
        GLShader screen_quad_shader;
};


#endif // WINDOWIMGUI_H
