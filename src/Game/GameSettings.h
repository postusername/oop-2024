#pragma once

#include <vector>
#include <cstddef>
#include <iostream>

struct GameSettings {
    size_t boardSize;
    std::vector<unsigned short> shipLengths;
    GameSettings();
    GameSettings(size_t boardSize, std::vector<unsigned short> shipLengths);

    friend std::ostream& operator<<(std::ostream& os, const GameSettings& gameMode);
    friend std::istream& operator>>(std::istream& is, GameSettings& gameMode);
};