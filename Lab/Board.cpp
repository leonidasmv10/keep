#include "Board.h"

#include <iostream>

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
