#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


int app_main(int argc, char* argv[]);

#if defined(_WIN32)

#include <Windows.h>
#include <cstdio>




int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int ncmdshow){
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    
    int result = app_main(__argc, __argv);
    std::cin.get();


    FreeConsole();
    return result;
}

#else

int main(int argc, char* argv[]){
    return app_main(argc, argv);
}

#endif

int app_main(int argc, char* argv[]) {
    // std::cout << "Hello, World!" << std::endl;
    
    if(!glfwInit()){
        std::cout << "Glfw initialization failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "i8080", nullptr, nullptr);
    if(!window){
        std::cerr << "Error Initializing window\n";
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    int step = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();


        ImGui::Begin("8080 Debug Window");
        ImGui::Text("Hello from ImGui!");
        ImGui::Text("Step: %d", step);

        if (ImGui::Button("Test Button")){
            step++;
        };
        ImGui::End();

        ImGui::Begin("CPU");
        ImGui::Text("A: %02X", 0x12);
        ImGui::End();

      
        ImGui::Begin("Memory");
        ImGui::Text("Memory viewer here");
        ImGui::End();


        ImGui::Begin("Controls");
        if (ImGui::Button("Run")) {}
        if (ImGui::Button("Step")) {}
        ImGui::End();

        ImGui::Render();
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            GLFWwindow* backup_current_context = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            glfwMakeContextCurrent(backup_current_context);
        }

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}