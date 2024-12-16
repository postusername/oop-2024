#include "Scanner.h"

Scanner::Scanner(GameBoard &enemyBoard) : enemyBoard(enemyBoard) {}

void Scanner::apply()
{
    enemyBoard.ship_found = false;
    auto coords = InputProcessor::readCoords();
    size_t x = coords.first, y = coords.second;
    if (x >= enemyBoard.getWidth() || y >= enemyBoard.getHeight()){
        throw InvalidAbilityCoordsException();
    }
    for(size_t i = x; i < x + 2; i++){
        for(size_t j = y; j < y + 2; j++){
            if (enemyBoard.isShip(j, i)){
                enemyBoard.ship_found = true;
                return;
            }
        }
    }
    enemyBoard.ship_found = false;
}

std::string Scanner::getName() {
    return "Scanner";
}
