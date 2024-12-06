#include "Cell.h"
#include <iostream>


Cell::Cell(ViewState status, Ship* ship, int shipSegment)
    : status(status), ship(ship), shipSegment(shipSegment) {}

Cell::Cell()
    : status(ViewState::Unknown), ship(nullptr), shipSegment(-1) {}

void Cell::placeShipSegment(Ship &ship, int shipSegment){
    this->ship = &ship;
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
    if (cell.ship) {
        os << cell.ship->getLength() << ' '; // Предполагается, что у Ship есть метод getLength()
    } else {
        os << "0 "; // Обозначение отсутствующего корабля (например, длина 0)
    }
    os << cell.shipSegment;
    return os;
}

std::istream& operator>>(std::istream& is, Cell& cell) {
    int statusInt;
    is >> statusInt;
    cell.status = static_cast<ViewState>(statusInt);

    unsigned short length;
    is >> length;
    if (length > 0) {
        cell.ship = new Ship(length, Orientation::Horizontal);
    } else {
        cell.ship = nullptr;
    }

    is >> cell.shipSegment;
    return is;
}
