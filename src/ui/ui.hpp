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
        void cpu_window(const core::CPU& cpu);
        void memory_window(const core::Memory& mem, const core::CPU &cpu);
        ImGuiIO& io;
    public:
        UI(GLFWwindow* window);
        void render(const core::CPU& cpu, const core::Memory& mem);
        void shutdown();
        ~UI();
    };


} // namespace i080::ui
