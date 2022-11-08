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
                player[i][j] = RED;
            }
            else if (i < 6)
            {
                player[i][j] = NONE;
            }
            else
            {
                player[i][j] = BLUE;
            }
        }
    }

    player[dx][dy] = SELECT;
}

void Board::Init()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            glm::vec3 position = glm::vec3(j * 2.1f - n, 0.0f, i * 2.1f - n);
            glm::vec3 scale = glm::vec3(0.4f);

            board[i][j] = new Quad2D(glm::vec3(j * 2.1f - n, -0.5f, i * 2.1f - n), scale);
            board[i][j]->SetColor(yellow);
            switch (player[i][j])
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

    for (const auto& c : board)
    {
        for (const auto& b : c)
        {
            b->Render(shader, camera);
        }
    }
}

void Board::Print()
{
    for (const auto& i : player)
    {
        for (const auto& j : i)
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}

void Board::MoveCube(const unsigned axisX, const unsigned axisY)
{
    int x = dx + axisX;
    int y = dy + axisY;
    if (x >= n && x < 0) return;
    if (y >= n && y < 0) return;
}
