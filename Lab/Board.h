#pragma once
#include <array>
#include <vector>

#include "Cube3D.h"

// non 0
// red 1
// blue 2
// select 3
// click 4

enum BoardDataType
{
    NONE,
    RED,
    BLUE,
    SELECT,
    CLICK
};

class Board
{
public:
    Board();

    void Init();
    void Render(Shader& shader, PerspectiveCamera& camera);
    void Print();

private:
    const int n = 8;
    BoardDataType board[8][8];
    // std::array<std::array<BoardDataType, 8>, 8> board;
    std::vector<Cube3D*> cubes;

    const glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    const glm::vec4 yellow = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};
