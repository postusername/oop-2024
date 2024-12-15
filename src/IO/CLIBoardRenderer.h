#pragma once

#include <string>

#include "../GameBoard.h"


class CLIBoardRenderer {
public:
    CLIBoardRenderer() = default;
    std::string render(GameBoard& board);
};
