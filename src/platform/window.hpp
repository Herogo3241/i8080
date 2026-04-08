#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace i8080::platform
{
    class Window
    {
    public:
        GLFWwindow* handle = nullptr;


        Window(const char* title, int width, int height);
        void begin_frame();
        void end_frame();
        bool should_close();
        void shutdown();
        ~Window();
    };
    
    
    
    
} // namespace i8080::platform
