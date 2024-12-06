#include "Bombing.h"

Bombing::Bombing(ShipManager& enemyShipManager)
    : enemyShipManager(enemyShipManager){}

void Bombing::apply() {
    OutputProcessor::showMessage("Bombing ability applied");
    int shipCount = enemyShipManager.getAliveShipsCount();
    int randomChoice = rand() % shipCount;
    Ship& ship = enemyShipManager.getAliveShip(randomChoice);
    randomChoice = rand() % ship.getLength();
    ship.takeDamage(randomChoice, 1);
}

std::string Bombing::getName() {
    return "Bombing";
}
