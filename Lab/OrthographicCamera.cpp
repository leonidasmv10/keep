#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(const Frustrum& frustrum, const glm::vec3& position, float rotation)
{
}

void OrthographicCamera::RecalculateMatrix()
{
    Camera::RecalculateMatrix();
}
