#include "Cell.h"
#include <iostream>


Cell::Cell(ViewState status, Ship* ship, int shipSegment)
    : status(status), ship(ship), shipSegment(shipSegment) {}

Cell::Cell()
    : status(ViewState::Unknown), ship(nullptr), shipSegment(-1) {}

void Cell::placeShipSegment(Ship* ship, int shipSegment){
    this->ship = ship;
    this->shipSegment = shipSegment;
}

void Cell::setStatus(ViewState status) {
    this->status = status;
}

ViewState Cell::getStatus() const {
    return this->status;
}

void Cell::attackShip(int damage = 1) {
    ship->takeDamage(this->shipSegment, damage);
}

bool Cell::isShip() const {
    return this->ship != nullptr;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os << static_cast<int>(cell.status) << ' ';
    return os;
}

std::istream& operator>>(std::istream& is, Cell& cell) {
    int statusInt;
    is >> statusInt;
    cell.status = static_cast<ViewState>(statusInt);
    return is;
}
