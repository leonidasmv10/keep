#include "PerspectiveCamera.h"

#include <glm/ext/matrix_transform.hpp>

#include "GLFW/glfw3.h"

PerspectiveCamera::PerspectiveCamera(const Frustrum& frustrum, const glm::vec3& position, const glm::vec3& lookAt,
                                     const glm::vec3& upVector)
{
    CameraFrustrum.angle = 45.0f;
}

void PerspectiveCamera::RecalculateMatrix()
{
    Camera::RecalculateMatrix();
    ViewMatrix = glm::lookAt(Position, glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
