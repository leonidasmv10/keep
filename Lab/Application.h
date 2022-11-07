#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GLFWApplication/GLFWApplication.h"

class Application
{
public:
    Application(const std::string& name, const std::string& version);
    ~Application();

    unsigned ParseArguments(int argc, char** argv);
    unsigned Init();
    unsigned Run();

private:
    GLuint vertexArrayId;
    GLuint vertexBufferId;

    GLFWwindow* window;
};
