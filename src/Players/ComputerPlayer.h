#pragma once

#include "../GameBoard.h"
#include "../ShipManager.h"
#include "../Game/GameSettings.h"
#include <random>
#include <set>

class ComputerPlayer {
private:
    GameBoard* aiBoard;
    ShipManager* aiShipManager;

public:
    ComputerPlayer();
    ~ComputerPlayer();
    void createShips(const GameSettings& gameMode);
    void makeMove(GameBoard& enemyBoard);
    GameBoard& getGameBoard();
    ShipManager& getShipManager();
    bool isDefeated();
    friend std::ostream& operator<<(std::ostream& os, const ComputerPlayer& player);
    friend std::istream& operator>>(std::istream& is, ComputerPlayer& player);
};