#include "Application.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << TEXTURES_DIR << "\n";
    std::cout << SHADERS_DIR << "\n";
    Application application("Lab1", "1.0");

    application.ParseArguments(argc, argv);
    application.Init();
    return application.Run();
}
