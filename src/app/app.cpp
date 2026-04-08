#include "app.hpp"
#include "../platform/window.hpp"
#include "../core/cpu/cpu.hpp"
#include "../core/memory/memory.hpp"
#include "../ui/ui.hpp"

namespace i8080::app
{
    App::App(){}

    void App::run(){
        platform::Window window("i8080", 800, 600);
        ui::UI ui(window.handle);

        core::Memory mem;
        core::CPU cpu(mem);


        
        while (!window.should_close())
        {
            window.begin_frame();

            ui.render(cpu);

            window.end_frame();
        }

        window.shutdown();
        
    }
    
} // namespace i8080::app
