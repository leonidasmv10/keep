#pragma once
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader();
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
    void UploadUniformBool(const std::string& name, bool value) const;
    void UploadUniformInt(const std::string& name, int value) const;
    void UploadUniformFloat(const std::string& name, float value) const;

private:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;

    void CompileShader(GLenum shaderType, const std::string& shaderSrc);
    void CheckCompileErrors(unsigned int shader, std::string type);
};
