#pragma once
#include <string>

#include "Board.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Cube3D.h"
#include "PerspectiveCamera.h"
#include "Shader.h"


class Application
{
public:
    Application(const std::string& name, const std::string& version);
    ~Application();

    unsigned ParseArguments(int argc, char** argv);
    unsigned Init();
    unsigned Run();
    
    static const int width = 800;
    static const int height = 800;

private:
    void Input(GLFWwindow* window);

    GLFWwindow* window;
    Shader *shader;
    PerspectiveCamera camera;
    Board *board;
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};
