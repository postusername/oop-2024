#pragma once

#include <string>
#include <iostream>
#include "../GameBoard.h"
#include "../ShipManager.h"

class OutputProcessor {
private:
    void drawBoard(GameBoard& board) const;
    void drawPlayerShips(ShipManager& shipManager) const;
public:
    void drawBoards(GameBoard& userBoard, GameBoard& aiBoard) const;
    void drawShips(ShipManager& userShipManager, ShipManager& aiShipManager) const;
    static void showMessage(const std::string& message);
};