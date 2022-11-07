#include "PerspectiveCamera.h"

#include <glm/ext/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(const Frustrum& frustrum, const glm::vec3& position, const glm::vec3& lookAt,
                                     const glm::vec3& upVector)
{
}

void PerspectiveCamera::RecalculateMatrix()
{
    Camera::RecalculateMatrix();
    ViewMatrix = glm::lookAt(Position, Position + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}
