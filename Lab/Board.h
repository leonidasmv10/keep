#pragma once
#include <array>

#include "Cube3D.h"

class Board
{
public:
    Board();

    void Init();

    void Render(Shader& shader, PerspectiveCamera& camera);

private:
    std::array<std::array<int, 8>, 8> board;
    std::array<std::array<Cube3D*, 8>, 8> cube;
};
