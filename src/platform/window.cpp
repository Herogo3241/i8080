#include "window.hpp"
#include <iostream>


namespace i8080::platform
{
    Window::Window(const char* title, int width, int height) {
        if (!glfwInit()) {
            std::cerr << "[GLFW] Initialization failed\n";
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!handle) {
            std::cerr << "[GLFW] Window creation failed\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(handle);
        glfwSwapInterval(1); // Enable VSync

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "[GLAD] Failed to initialize\n";
            glfwDestroyWindow(handle);
            glfwTerminate();
        }
    }

    void Window::begin_frame() {
        glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize(handle, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::end_frame() {
        glfwSwapBuffers(handle);
    }

    bool Window::should_close() {
        return glfwWindowShouldClose(handle);
    }

    void Window::shutdown() {
        if (handle) {
            glfwDestroyWindow(handle);
        }
        glfwTerminate();

    }

    Window::~Window() {
        shutdown();
    }

} // namespace i8080::platform
