#pragma once
#include <array>
#include <vector>

#include "Cube3D.h"

// non 0
// red 1
// blue 2
// select 3

enum BoardDataType
{
    NONE,
    RED,
    BLUE,
    SELECT
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
    std::vector<Cube3D*> cube;
};
