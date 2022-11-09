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
    color = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    this->Init();
}

Cube3D::Cube3D(const glm::vec3& position, const glm::vec3& scale)
{
    this->position = position;
    this->scale = scale;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->Init();
}

Cube3D::~Cube3D()
{
   
}

void Cube3D::Init()
{
    vertexArray = std::make_shared<VertexArray>();
    vertexArray->Bind();

    vertexBuffer = std::make_shared<VertexBuffer>(GeometricTools::UnitCube3D, 5);

    vertexBuffer->BufferSubData(3, 5, (void*)0);
    vertexBuffer->BufferSubData(2, 5, (void*)(3 * sizeof(float)));

    vertexArray->AddVertexBuffer(vertexBuffer);
}

void Cube3D::Render(Shader& shader, PerspectiveCamera& camera)
{
    glActiveTexture(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);

    shader.Bind();
    
    glm::mat4 model = glm::mat4(1.0f);
    const glm::mat4 projection = camera.GetProjectionMatrix();
    const glm::mat4 view = camera.GetViewMatrix();

    shader.UploadUniformMat4("projection", projection);
    shader.UploadUniformMat4("view", view);
    
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    
    shader.UploadUniformMat4("model", model);
    shader.UploadUniformVec4("color", color);
    
    vertexArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
