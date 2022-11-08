#include "Board.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

Board::Board()
{
    bool flag = true;
    for (auto& i : board)
    {
        for (auto& j : i)
        {
            j = flag;
            flag = !flag;
        }
        flag = !flag;
    }

    for (const auto& i : board)
    {
        for (const auto& j : i)
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}

void Board::Init()
{
    int n = 8;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            glm::vec3 position = glm::vec3(j * 2.1f - n, 1.0f, i * 2.1f - n);
            glm::vec3 scale = glm::vec3(0.4f);
            cube[i][j] = new Cube3D(position, scale);
        }
    }
}

void Board::Render(Shader& shader, PerspectiveCamera& camera)
{
    for (const auto& i : cube)
    {
        for (const auto& j : i)
        {
            j->Render(shader, camera);
        }
    }
}
