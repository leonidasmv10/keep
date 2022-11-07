#pragma once
#include "Camera.h"
#include "Shader.h"

class Cube3D
{
public:
    Cube3D();

    void Init();
    void Render(Shader &shader,Camera &camera);


private:
    unsigned int VBO, VAO;
};
