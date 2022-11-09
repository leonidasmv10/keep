#include "Quad2D.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Application.h"
#include "GeometricTools.h"

Quad2D::Quad2D()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->Init();
}

Quad2D::Quad2D(const glm::vec3& position, const glm::vec3& scale)
{
    this->position = position;
    this->scale = scale;
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    this->Init();
}

Quad2D::~Quad2D()
{
}

void Quad2D::Init()
{
    vertexArray = std::make_shared<VertexArray>();
    vertexBuffer = std::make_shared<VertexBuffer>(GeometricTools::UnitQuad2D, sizeof(GeometricTools::UnitQuad2D));
    elementBuffer = std::make_shared<IndexBuffer>(GeometricTools::InidicesQuad2D, sizeof(GeometricTools::UnitQuad2D));
    
    vertexArray->Bind();
    vertexBuffer->Bind();
    elementBuffer->Bind();
    
    vertexArray->AttribPointer(3, 3, (void*)0);

    vertexBuffer->Unbind();
    vertexArray->Unbind();
    elementBuffer->Unbind();

    vertexArray->AddVertexBuffer(vertexBuffer);
}

void Quad2D::Render(Shader& shader, PerspectiveCamera& camera)
{
    shader.Bind();

    const glm::mat4 projection = glm::perspective(camera.GetAngle(),
                                                  static_cast<float>(Application::width) / static_cast<float>(
                                                      Application::height), 0.1f,
                                                  100.0f);

    shader.UploadUniformMat4("projection", projection);

    const glm::mat4 view = camera.GetViewMatrix();
    shader.UploadUniformMat4("view", view);
    shader.UploadUniformVec4("color", color);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    shader.UploadUniformMat4("model", model);

    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
