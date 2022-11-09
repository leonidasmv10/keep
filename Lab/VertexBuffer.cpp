#include "VertexBuffer.h"

#include "GeometricTools.h"

VertexBuffer::VertexBuffer(const float* vertices, GLsizei size)
{
    glGenBuffers(1, &VertexBufferID);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GeometricTools::UnitCube3D), GeometricTools::UnitCube3D,
                 GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &VertexBufferID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLsizeiptr size, GLintptr offset, const void* data) 
{
    glVertexAttribPointer(IdVertexAttrib, size, GL_FLOAT, GL_FALSE, offset * sizeof(float), data);
    glEnableVertexAttribArray(IdVertexAttrib++);
}
