#include "Board.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


Board::Board()
{
    lastColorCube = red;
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
            }

            board[i][j] = new Quad2D(glm::vec3(j * 2.0f - n, -0.5f, i * 2.0f - n), scale);
            board[i][j]->SetColor(flag ? black : white);
            flag = !flag;
        }
        flag = !flag;
    }
    board[dx][dy]->SetColor(green);
    cubes[dx][dy]->SetColor(green);
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

void Board::Move(const unsigned axisX, const unsigned axisY)
{
    int x = dx + axisX;
    int y = dy + axisY;
    if (x >= n || x < 0) return;
    if (y >= n || y < 0) return;

    board[dx][dy]->SetColor(lastColorBoard);

    if (cubes[dx][dy] != nullptr)
        cubes[dx][dy]->SetColor(lastColorCube);

    dx = x;
    dy = y;

    lastColorBoard = board[dx][dy]->GetColor();
    board[dx][dy]->SetColor(green);
    if (cubes[dx][dy] != nullptr)
    {
        lastColorCube = cubes[dx][dy]->GetColor();
        lastColorClick = cubes[dx][dy]->GetColor();
        cubes[dx][dy]->SetColor(green);
    }
}

void Board::MoveCube()
{
    if (!hasPair)
    {
        if (cubes[dx][dy] == nullptr) return;
        cubes[dx][dy]->SetColor(yellow);
        lastColorCube = yellow;
        cubeClickPos = std::pair(dx, dy);
        hasPair = true;
    }
    else
    {
        if (player[dx][dy] != NONE) return;

        int px = cubeClickPos.first;
        int py = cubeClickPos.second;

        player[px][py] = NONE;

        cubes[px][py]->SetPosition(glm::vec3(dy * 2.0f - n, 0.0f, dx * 2.0f - n));
        cubes[px][py]->SetColor(green);

        auto temp = cubes[dx][dy];
        cubes[dx][dy] = cubes[px][py];
        cubes[px][py] = temp;

        lastColorCube = lastColorClick;

        if (lastColorClick == red)
            player[dx][dy] = RED;

        else if (lastColorClick == blue)
            player[dx][dy] = BLUE;

        hasPair = false;
    }
}
