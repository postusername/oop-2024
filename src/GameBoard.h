#pragma once

#include <iostream>
#include <iomanip>
#include "Ship.h"
#include "Cell.h"
#include "ShipManager.h"
#include "Exceptions/ShipException.h"
#include "Exceptions/AttackCoordsException.h"


class GameBoard {
    private:
        std::vector<std::vector<Cell>> board;
        size_t height;
        size_t width;
        void checkShipCoords(size_t x, size_t y, Ship* ship) const;
        void checkAttackCoords(size_t x, size_t y) const;
    public:
        bool ship_found = false;
        const Cell& operator()(size_t x, size_t y);
        GameBoard() = default;
        GameBoard(size_t height, size_t width);
        GameBoard(const GameBoard& other);
        GameBoard(GameBoard&& other) noexcept ;
        GameBoard& operator=(const GameBoard &other);
        GameBoard& operator=(GameBoard &&other);
        void placeShip(size_t x, size_t y, Ship* ship);
        void attackCell(size_t x, size_t y, int damage = 1);
        bool isShip(size_t x, size_t y) const;
        size_t getHeight() const;
        size_t getWidth() const;
        friend std::ostream& operator<<(std::ostream& os, const GameBoard& board);
        friend std::istream& operator>>(std::istream& is, GameBoard& board);
};