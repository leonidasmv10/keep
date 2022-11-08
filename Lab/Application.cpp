#include "Application.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GeometricTools.h"
#include "TextureManager.h"

Application::Application(const std::string& name, const std::string& version)
{
    glfwSetErrorCallback([](int code, const char* description)
    {
        glfwGetError(&description);
        std::cerr << "Error " << "0x" << std::hex << code << ':' << description << "\n";
    });

    // Initialization of glfw.
    if (!glfwInit())
    {
        std::cin.get();
        return;
    }

    // Create a window
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        std::cin.get();
        return;
    }

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto w = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (w->key_input) w->key_input(key, scancode, action, mods);
    });
    glfwSetWindowUserPointer(window, this);

    //Set the OpenGL context
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    InputCallback();

    // Enable capture of debug output.
    glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(
    //     [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    //        const GLchar* message, const void* userParam)
    //     {
    //         std::cerr << "GL CALLBACK:" << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
    //             "type = 0x" << type <<
    //             ", severity = 0x" << severity <<
    //             ", message =" << message << "\n";
    //     }, 0);

    glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{
    glfwTerminate();
}

unsigned Application::ParseArguments(int argc, char** argv)
{
    return 1;
}

unsigned Application::Init()
{
    // Print OpenGL data
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";


    shader = new Shader(std::string(SHADERS_DIR) + "model.vert", std::string(SHADERS_DIR) + "model.frag");

    camera = PerspectiveCamera();
    camera.SetMovement(1, 0.0);

    board = new Board();
    board->Init();

    TextureManager::GetInstance()->LoadTexture2DRGBA("container",
                                                     std::string(TEXTURES_DIR) + "container.jpg",
                                                     0, false);

    TextureManager::GetInstance()->LoadTexture2DRGBA("awesomeface",
                                                     std::string(TEXTURES_DIR) + "awesomeface.png",
                                                     1, true);

    shader->Bind();
    shader->UploadUniformInt("texture1", 0);
    shader->UploadUniformInt("texture2", 1);

    return 1;
}

unsigned Application::Run()
{
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Input(window);

        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        board->Render(*shader, camera);
        
        glfwSwapBuffers(window);
    }

    return 1;
}

void Application::InputCallback()
{
    key_input = [&](int key, int sancode, int action, int mods)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            board->MoveCube(-1,0);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            board->MoveCube(1,0);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            board->MoveCube(0,1);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            board->MoveCube(0,-1);
        }
    };
}

void Application::Input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        camera.SetMovement(deltaTime, 1.f);

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        camera.SetMovement(deltaTime, -1.f);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        camera.SetAngle(camera.GetAngle() - 1.0f * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        camera.SetAngle(camera.GetAngle() + 1.0f * deltaTime);
}
