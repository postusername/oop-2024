#include "GameSettings.h"
#include <sstream>

GameSettings::GameSettings() {}

GameSettings::GameSettings(size_t boardSize, std::vector<unsigned short> shipLengths)
    : boardSize(boardSize), shipLengths(std::move(shipLengths)){}

std::ostream& operator<<(std::ostream& os, const GameSettings& gameMode) {
    os << gameMode.boardSize << '\n';
    os << gameMode.shipLengths.size() << '\n';
    for (size_t length : gameMode.shipLengths) {
        os << length << ' ';
    }
    os << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, GameSettings& gameMode) {
    try {
        is >> gameMode.boardSize;
        size_t shipCount;
        is >> shipCount;
        gameMode.shipLengths.reserve(shipCount);

        for (size_t i = 0; i < shipCount; ++i) {
            unsigned short length;
            is >> length;
            gameMode.shipLengths.push_back(length);
        }
    } catch (const std::ios_base::failure& e) {
        throw std::ios_base::failure("Error reading GameSettings: " + std::string(e.what()));
    }
    return is;
}