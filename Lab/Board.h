#pragma once
#include <array>
#include <vector>

#include "Cube3D.h"
#include "Quad2D.h"

// non 0
// red 1
// blue 2

enum BoardDataType
{
    NONE,
    RED,
    BLUE,
};

class Board
{
public:
    Board();
    void Init();
    void Render(Shader& shader, PerspectiveCamera& camera);
    void Print();
    void Move(const unsigned axisX, const unsigned axisY);
    void MoveCube();

private:
    // SIZE
    const int n = 8;

    // MATRIX
    BoardDataType player[8][8];
    Quad2D* board[8][8];
    Cube3D* cubes[8][8];

    // MOVE BOARD
    unsigned dx = 0, dy = 0;
    glm::vec4 lastColorCube;
    glm::vec4 lastColorBoard;

    // MOVE CUBE
    bool hasPair = false;
    std::pair<int,int> cubeClickPos;
    glm::vec4 lastColorClick;

    // COLOR

    const glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    const glm::vec4 yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    const glm::vec4 white = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};
