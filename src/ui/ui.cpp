#include "ui.hpp"
#include <cstdio>




namespace i8080::ui
{
    void UI::cpu_window(const core::CPU& cpu) {
        ImGui::Begin("CPU State");

        
        if (ImGui::CollapsingHeader("Registers", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::BeginTable("RegTable", 2, ImGuiTableFlags_NoSavedSettings)) {
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                ImGui::TableSetupColumn("Value");

                // Helper to draw a row with coloring
                auto DrawReg = [](const char* name, uint16_t val, ImVec4 color = ImVec4(1, 1, 1, 1)) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextDisabled("%s:", name);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::TextColored(color, "0x%04X", val);
                    ImGui::SameLine();
                    ImGui::TextDisabled("(%d)", val); 
                    };

                DrawReg("PSW", cpu.PSW(), ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
                DrawReg("BC", cpu.BC());
                DrawReg("DE", cpu.DE());
                DrawReg("HL", cpu.HL());

                ImGui::TableNextRow(); ImGui::TableSetColumnIndex(0); ImGui::Separator(); ImGui::TableSetColumnIndex(1); ImGui::Separator();

                DrawReg("SP", cpu.SP, ImVec4(0.4f, 1.0f, 1.0f, 1.0f));
                DrawReg("PC", cpu.PC, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); 

                ImGui::EndTable();
            }
        }

        ImGui::Spacing();

       
        if (ImGui::CollapsingHeader("Flags", ImGuiTreeNodeFlags_DefaultOpen)) {
            auto DrawFlag = [](const char* label, bool set) {
                if (set) ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", label);
                else ImGui::TextDisabled("%s", label);
                ImGui::SameLine();
                };

            ImGui::Text("Bits: "); ImGui::SameLine();
            DrawFlag("S", cpu.flags.S);
            DrawFlag("Z", cpu.flags.Z);
            DrawFlag("AC", cpu.flags.AC);
            DrawFlag("P", cpu.flags.P);
            DrawFlag("C", cpu.flags.C);

            ImGui::NewLine();
            ImGui::TextDisabled("Byte: 0x%02X", cpu.flags.to_byte());
        }

        ImGui::End();
    }

    void UI::memory_window(const core::Memory& mem, const core::CPU& cpu) {
        ImGui::Begin("Memmory Map");
        const uint8_t* raw_data = mem.get_all_data();
        const uint16_t pc_addr = cpu.PC;

        static ImGuiTableFlags flags =
            ImGuiTableFlags_BordersV |
            ImGuiTableFlags_BordersOuterH |
            ImGuiTableFlags_RowBg |
            ImGuiTableFlags_ScrollY |
            ImGuiTableFlags_Hideable;

        if (ImGui::BeginTable("MemTable", 18, flags, ImVec2(0, 0))) { // 1 (Addr) + 16 (Data) + 1 (Ascii)
            ImGui::TableSetupColumn("Addr", ImGuiTableColumnFlags_WidthFixed, 40.0f);
            for (int i = 0; i < 16; i++) {
                char buf[3];
                sprintf(buf, "%02X", i);
                ImGui::TableSetupColumn(buf, ImGuiTableColumnFlags_WidthFixed, 22.0f);
            }
            ImGui::TableSetupColumn("ASCII", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();

            ImGuiListClipper clipper;
            clipper.Begin(4096);

            while (clipper.Step()) {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
                    uint16_t row_addr = i * 16;
                    ImGui::TableNextRow();


                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextDisabled("%04X", row_addr);


                    for (int j = 0; j < 16; j++) {
                        ImGui::TableSetColumnIndex(j + 1);
                        uint16_t current_addr = row_addr + j;
                        uint8_t val = raw_data[current_addr];

                        if (current_addr == pc_addr) {
                            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%02X", val);
                        }
                        else if (val == 0) {
                            ImGui::TextDisabled("00");
                        }
                        else {
                            ImGui::Text("%02X", val);
                        }
                    }

                    ImGui::TableSetColumnIndex(17);
                    char ascii[17];
                    for (int j = 0; j < 16; j++) {
                        uint8_t val = raw_data[row_addr + j];
                        ascii[j] = (val >= 32 && val <= 126) ? (char)val : '.';
                    }
                    ascii[16] = '\0';
                    ImGui::Text("%s", ascii);
                }
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }




    UI::UI(GLFWwindow* window) : io((ImGui::CreateContext(), ImGui::GetIO())) {
        IMGUI_CHECKVERSION();

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void UI::render(const core::CPU& cpu, const core::Memory& mem) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();

        // UI for logging emulation data
        cpu_window(cpu);
        memory_window(mem, cpu);

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

    UI::~UI() {
        shutdown();
    }

} // namespace i080::ui
