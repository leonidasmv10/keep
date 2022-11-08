#include "Application.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Application application("Lab1", "1.0");

    application.ParseArguments(argc, argv);
    application.Init();
    return application.Run();
}
