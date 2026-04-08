#include "ui.hpp"




namespace i8080::ui
{
    void UI::draw_cpu_window(core::CPU& cpu){
        ImGui::Begin("CPU");

        ImGui::Text("PSW: %04X", cpu.PSW());
        ImGui::Text("BC: %04X", cpu.BC());
        ImGui::Text("DE: %04X", cpu.DE());
        ImGui::Text("HL: %04X", cpu.HL());
        ImGui::Text("SP: %04X", cpu.SP);
        ImGui::Text("PC: %04X", cpu.PC);

        ImGui::End();
    }

    

    UI::UI(GLFWwindow* window) : io( (ImGui::CreateContext(), ImGui::GetIO()) ){
        IMGUI_CHECKVERSION();

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;    
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void UI::render(core::CPU& cpu){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();

        // UI for logging emulation data
        draw_cpu_window(cpu);

        ImGui::Render();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UI::shutdown() {
        if (ImGui::GetCurrentContext() != nullptr) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    UI::~UI(){
        shutdown();
    }
    
} // namespace i080::ui
