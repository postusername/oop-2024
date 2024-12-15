#pragma once

#include "../Game/GameSettings.h"
#include "../SkillManager.h"
#include "../GameBoard.h"
#include "../ShipManager.h"

class UserPlayer {
private:
    GameBoard* userBoard;
    ShipManager* userShipManager;
    SkillManager* skillManager;
    void attack(GameBoard& enemyBoard, ShipManager& enemyShipManager);
    void useSkill();

public:
    UserPlayer(const GameSettings &gameMode, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords);
    UserPlayer(GameBoard& enemyBoard, ShipManager& enemyShipManager);
    ~UserPlayer();
    GameBoard& getGameBoard();
    ShipManager& getShipManager();
    SkillManager& getAbilityManager();
    void createShips(const GameSettings &gameMode,
                     std::vector<Orientation> orientations,
                     std::vector<std::pair<size_t, size_t>> coords);
    Option makeMove(GameBoard& enemyBoard, ShipManager& enemyShipManager);
    bool isDefeated();
    friend std::ostream& operator<<(std::ostream& os, const UserPlayer& player);
    friend std::istream& operator>>(std::istream& is, UserPlayer& player);
};