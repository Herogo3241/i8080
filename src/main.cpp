#include <iostream>
#include "app/app.hpp"



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
    i8080::app::App app;
    app.run();
    return 0;
}
