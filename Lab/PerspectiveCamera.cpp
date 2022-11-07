#include "PerspectiveCamera.h"

#include <glm/ext/matrix_transform.hpp>

#include "GLFW/glfw3.h"

PerspectiveCamera::PerspectiveCamera(const Frustrum& frustrum, const glm::vec3& position, const glm::vec3& lookAt,
                                     const glm::vec3& upVector)
{
}

void PerspectiveCamera::RecalculateMatrix()
{
    Camera::RecalculateMatrix();
    float radius = 10.0f;
    float camX = static_cast<float>(sin(glfwGetTime()) * radius);
    float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
    ViewMatrix = glm::lookAt(glm::vec3(camX, 2.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // ViewMatrix = glm::lookAt(Position, Position + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}
