#include "Board.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


Board::Board()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < 2)
            {
                board[i][j] = RED;
            }
            else if (i < 6)
            {
                board[i][j] = NONE;
            }
            else
            {
                board[i][j] = BLUE;
            }
        }
    }

    board[0][0] = SELECT;
}

void Board::Init()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            glm::vec3 position = glm::vec3(j * 2.1f - n, 1.0f, i * 2.1f - n);
            glm::vec3 scale = glm::vec3(0.4f);


            switch (board[i][j])
            {
            case RED:
                cubes.push_back(new Cube3D(position, scale));
                cubes.back()->SetColor(red);
                break;

            case BLUE:
                cubes.push_back(new Cube3D(position, scale));
                cubes.back()->SetColor(blue);
                break;

            case SELECT:
                cubes.push_back(new Cube3D(position, scale));
                cubes.back()->SetColor(green);
                break;
            }
        }
    }
}

void Board::Render(Shader& shader, PerspectiveCamera& camera)
{
    for (const auto& c : cubes)
    {
        c->Render(shader, camera);
    }
}

void Board::Print()
{
    for (const auto& i : board)
    {
        for (const auto& j : i)
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}
