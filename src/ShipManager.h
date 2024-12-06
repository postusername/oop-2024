#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Ship.h"

class ShipManager {
    private:
        std::vector<Ship*> ships;
        int shipCount;
        std::vector<unsigned short> shipLengths;
    public:
        ShipManager();
        ShipManager(std::vector<unsigned short> shipLengths);
        ~ShipManager();
        void addShip(Ship* ship);
        bool allShipsDestroyed() const;
        int getAliveShipsCount() const;
        int getShipsCount() const;
        Ship* operator[](unsigned short index);
        Ship& getAliveShip(unsigned short index);
        friend std::istream& operator>>(std::istream& is, ShipManager& manager);
        friend std::ostream& operator<<(std::ostream& os, ShipManager& manager);
};