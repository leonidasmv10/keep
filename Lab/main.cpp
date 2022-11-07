#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Application.h"

int main(int argc, char *argv[])
{
    Application application("Lab1", "1.0");

    application.ParseArguments(argc, argv);
    application.Init();
    return application.Run();
}
