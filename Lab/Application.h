#pragma once
#include <string>

#include "Board.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera_Test.h"
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

    void processInput(GLFWwindow *window);

    
private:
    GLuint vertexArrayId;
    GLuint vertexBufferId;

    GLFWwindow* window;

    unsigned int texture;
    Shader ourShader;
    unsigned int VBO, VAO, EBO;

    unsigned int texture1, texture2,index_t;
    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    
    PerspectiveCamera camera;

    Board board;
    
    // Camera_Test camera;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    GLuint vao_{};
    
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
};
