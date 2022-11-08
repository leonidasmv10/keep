#include "Board.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


Board::Board()
{
    lastColorPlayer = red;
    lastColorBoard = white;
    
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
    bool flag = false;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            glm::vec3 position = glm::vec3(j * 2.0f - n, 0.0f, i * 2.0f - n);
            glm::vec3 scale = glm::vec3(0.4f);

            cubes[i][j] = nullptr;

            switch (player[i][j])
            {
            case RED:
                cubes[i][j] = new Cube3D(position, scale);
                cubes[i][j]->SetColor(red);
                break;

            case BLUE:
                cubes[i][j] = new Cube3D(position, scale);
                cubes[i][j]->SetColor(blue);
                break;

            case SELECT:
                cubes[i][j] = new Cube3D(position, scale);
                cubes[i][j]->SetColor(green);
                break;
            }

            board[i][j] = new Quad2D(glm::vec3(j * 2.0f - n, -0.5f, i * 2.0f - n), scale);
            board[i][j]->SetColor(flag ? black : white);
            flag = !flag;
        }
        flag = !flag;
    }
    board[dx][dy]->SetColor(green);
}

void Board::Render(Shader& shader, PerspectiveCamera& camera)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j]->Render(shader, camera);
            if (cubes[i][j] == nullptr) continue;
            cubes[i][j]->Render(shader, camera);
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
    if (x >= n || x < 0) return;
    if (y >= n || y < 0) return;
    // std::cout << "x: " << x << "\n";

    board[dx][dy]->SetColor(lastColorBoard);

    if (cubes[dx][dy] != nullptr)
        cubes[dx][dy]->SetColor(lastColorPlayer);

    dx = x;
    dy = y;

    lastColorBoard = board[dx][dy]->GetColor();
    board[dx][dy]->SetColor(green);
    if (cubes[dx][dy] != nullptr)
    {
        lastColorPlayer = cubes[dx][dy]->GetColor();
        cubes[dx][dy]->SetColor(green);
    }
}
