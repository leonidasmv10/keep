#pragma once
#include "Camera.h"
#include "PerspectiveCamera.h"
#include "Shader.h"

class Cube3D
{
public:
    Cube3D();
    Cube3D(const glm::vec3& position, const glm::vec3& scale);
    ~Cube3D();

    void Init();
    void Render(Shader& shader, PerspectiveCamera& camera);

    void SetPosition(const glm::vec3& position)
    {
        this->position = position;
    }

    void SetScale(const glm::vec3& scale)
    {
        this->scale = scale;
    }

    void SetColor(const glm::vec4& color)
    {
        this->color = color;
    }

    glm::vec3 GetPosition() const
    {
        return this->position;
    }

    glm::vec3 GetScale() const
    {
        return this->scale;
    }

    glm::vec4 GetColor() const
    {
        return this->color;
    }

private:
    unsigned int VBO, VAO;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec4 color;
};
