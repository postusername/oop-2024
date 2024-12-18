#pragma once

#include <memory>
#include "Ship.h"

enum class ViewState {
    Unknown,
    Empty,
    Ship,
    Destroyed,
};

class Cell {
    private:
        ViewState status;
        int shipSegment;
    public:
        Ship* ship;
        Cell(ViewState status, Ship* ship, int shipSegment);
        Cell();
        void placeShipSegment(Ship* ship, int shipSegment);
        void setStatus(ViewState status);
        void attackShip(int damage);
        ViewState getStatus() const;
        bool isShip() const;
        friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
        friend std::istream& operator>>(std::istream& is, Cell& cell);
};