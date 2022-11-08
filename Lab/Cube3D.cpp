#include "Cube3D.h"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Application.h"
#include "GeometricTools.h"
#include "VertexArray.h"

Cube3D::Cube3D()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->Init();
}

Cube3D::Cube3D(const glm::vec3& position, const glm::vec3& scale)
{
    this->position = position;
    this->scale = scale;
    this->Init();
}

Cube3D::~Cube3D()
{
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Cube3D::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GeometricTools::UnitCube3D), GeometricTools::UnitCube3D,
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Cube3D::Render(Shader& shader, PerspectiveCamera& camera)
{
    /*glActiveTexture(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);*/

    shader.Bind();

    const glm::mat4 projection = glm::perspective(camera.GetAngle(),
                                                  static_cast<float>(Application::width) / static_cast<float>(
                                                      Application::height), 0.1f,
                                                  100.0f);

    shader.UploadUniformMat4("projection", projection);

    const glm::mat4 view = camera.GetViewMatrix();
    shader.UploadUniformMat4("view", view);
    //shader.UploadUniformVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    shader.UploadUniformMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
