#pragma once
#include "../core/cpu/cpu.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace i8080::ui
{
    class UI
    {
    private:
        void draw_cpu_window(core::CPU& cpu);
        ImGuiIO& io;
    public:
        UI(GLFWwindow* window);
        void render(core::CPU& cpu);
        void shutdown();
        ~UI();
    };


} // namespace i080::ui
