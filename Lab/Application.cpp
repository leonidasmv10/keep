#include "Application.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    window = glfwCreateWindow(800, 600, name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        std::cin.get();
        return;
    }

    //Set the OpenGL context
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

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
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteVertexArrays(1, &vertexArrayId);
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


    shader = Shader(std::string(SHADERS_DIR) + std::string("model.vert"),
                       std::string(SHADERS_DIR) + std::string("model.frag"));

    camera = PerspectiveCamera();
    board = Board();
    cube = Cube3D();

    cube.Init();


    TextureManager::GetInstance()->LoadTexture2DRGBA("container",
                                                     "resources/textures/container.jpg",
                                                     0, false);

    TextureManager::GetInstance()->LoadTexture2DRGBA("awesomeface",
                                                     "resources/textures/awesomeface.png",
                                                     1, true);
    

    shader.Bind();
    shader.UploadUniformInt("texture1", 0);
    shader.UploadUniformInt("texture2", 1);
    
    return 1;
}

unsigned Application::Run()
{
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        cube.Render(shader, camera);

        glfwSwapBuffers(window);
    }

    return 1;
}


void Application::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 pos = camera.GetPosition();
        pos += glm::vec3(0, 0, -1) * 1.0f * deltaTime;
        camera.SetPosition(pos);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 pos = camera.GetPosition();
        pos += glm::vec3(0, 0, 1) * 1.0f * deltaTime;
        camera.SetPosition(pos);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 pos = camera.GetPosition();
        pos += glm::vec3(1, 0, 0) * 1.0f * deltaTime;
        camera.SetPosition(pos);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 pos = camera.GetPosition();
        pos += glm::vec3(-1, 0, 0) * 1.0f * deltaTime;
        camera.SetPosition(pos);
    }
}
