#include "Cube3D.h"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "GeometricTools.h"
#include "VertexArray.h"

Cube3D::Cube3D()
{
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

void Cube3D::Render(Shader& shader, Camera& camera)
{
    glActiveTexture(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);

    shader.Bind();

    glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f,
                                            100.0f);
    shader.UploadUniformMat4("projection", projection);

    const glm::mat4 view = camera.GetViewMatrix();
    shader.UploadUniformMat4("view", view);
    
    glBindVertexArray(VAO);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));
    float angle = 0.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    shader.UploadUniformMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
