#include "Bombing.h"

Bombing::Bombing(ShipManager& enemyShipManager) {}

void Bombing::apply(size_t ax, size_t ay, GameBoard &enemyBoard, ShipManager &enemyShipManager) {
    int shipCount = enemyShipManager.getAliveShipsCount();
    int randomChoice = rand() % shipCount;
    Ship& ship = enemyShipManager.getAliveShip(randomChoice);
    randomChoice = rand() % ship.getLength();
    ship.takeDamage(randomChoice, 1);
}

std::string Bombing::getName() {
    return "Bombing";
}
