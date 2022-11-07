#pragma once
#include <string>

#include "Board.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera_Test.h"
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

    void processInput(GLFWwindow* window);


private:
    GLuint vertexArrayId;
    GLuint vertexBufferId;

    GLFWwindow* window;

    unsigned int texture;
    Shader shader;
    unsigned int VBO, VAO, EBO;

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    PerspectiveCamera camera;

    Board board;

    Cube3D cube = Cube3D();


    // timing
    float deltaTime = 0.0f; // time between current frame and last frame
    float lastFrame = 0.0f;
};
