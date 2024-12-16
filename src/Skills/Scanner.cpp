#include "Scanner.h"

Scanner::Scanner(GameBoard &enemyBoard) {}

void Scanner::apply(size_t ax, size_t ay, GameBoard &enemyBoard, ShipManager &enemyShipManager)
{
    enemyBoard.ship_found = false;
    if (ax >= enemyBoard.getWidth() || ay >= enemyBoard.getHeight()){
        throw InvalidAbilityCoordsException();
    }
    for(size_t i = ax; i < ax + 2; i++){
        for(size_t j = ay; j < ay + 2; j++){
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
