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
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Quad2D::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GeometricTools::UnitQuad2D), GeometricTools::UnitQuad2D, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GeometricTools::InidicesQuad2D), GeometricTools::InidicesQuad2D, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
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
    
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}
