#include "ShipManager.h"


ShipManager::ShipManager() {}

ShipManager::ShipManager(std::vector<unsigned short> shipLengths)
    : shipCount(std::size(shipLengths)), shipLengths(shipLengths) {}

int ShipManager::getShipsCount() const {
    return this->shipCount;
}

bool ShipManager::allShipsDestroyed() const{
    return getAliveShipsCount() == 0;
}

int ShipManager::getAliveShipsCount() const{
    return std::count_if(ships.begin(), ships.end(), 
    [](const Ship* ship) { return !ship->isDestroyed(); });
}

void ShipManager::addShip(Ship* ship) {
    this->ships.push_back(ship);
}

Ship& ShipManager::operator[](unsigned short index) {
    if (index >= this->shipCount) {
        throw std::out_of_range("Ship index out of range");
    }
    return *(this->ships[index]);
}

Ship& ShipManager::getAliveShip(unsigned short index){
    std::vector<Ship*> aliveShips;
    std::copy_if(ships.begin(), ships.end(), std::back_inserter(aliveShips),
        [](const Ship* ship) { return !ship->isDestroyed(); });
    return *(aliveShips[index]);
}

ShipManager::~ShipManager() {
    for (Ship* ship : ships) {
        delete ship;
    }
    ships.clear();
}

std::ostream& operator<<(std::ostream& os, ShipManager& manager) {
    os << manager.getShipsCount() << '\n';
    for (size_t i = 0; i < manager.getShipsCount(); ++i) {
        os << manager[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, ShipManager& manager) {
    is >> manager.shipCount;

    for (unsigned short i = 0; i < manager.shipCount; ++i) {
        Ship* ship = new Ship(0, Horizontal);
        is >> *ship;
        manager.addShip(ship);
    }

    return is;
}
