#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include <glad/glad.h>

class VertexBuffer
{
public:
    // Constructor. It initializes with a data buffer and the size of it.
    // Note that the buffer will be bound on construction.
    VertexBuffer(const void *vertices, GLsizei size);
    ~VertexBuffer();

    // Bind the vertex buffer
    void Bind() const;

    // Unbind the vertex buffer
    void Unbind() const;

    // Fill out a specific segment of the buffer given by an offset and a size.
    void BufferSubData(GLintptr offset, GLsizeiptr size, const void *data) const;

private:
    GLuint VertexBufferID;
};

#endif // VERTEXBUFFER_H_
