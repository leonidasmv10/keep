#pragma once
#include <string>

#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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

    unsigned int texture;
    Shader ourShader;
    unsigned int VBO, VAO, EBO;
};
