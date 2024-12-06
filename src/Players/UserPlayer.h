#pragma once

#include "../IO/InputProcessor.h"
#include "../SkillManager.h"
#include "../GameBoard.h"
#include "../ShipManager.h"

class UserPlayer {
private:
    GameBoard* userBoard;
    ShipManager* userShipManager;
    SkillManager* skillManager;
    InputProcessor& inputProcessor;
    void attack(GameBoard& enemyBoard, ShipManager& enemyShipManager);
    void useSkill();

public:
    UserPlayer(InputProcessor& inputProcessor);
    UserPlayer(InputProcessor& inputProcessor, GameBoard& enemyBoard, ShipManager& enemyShipManager);
    ~UserPlayer();
    GameBoard& getGameBoard();
    ShipManager& getShipManager();
    SkillManager& getAbilityManager();
    void createShips(const GameSettings& gameMode);
    Option makeMove(GameBoard& enemyBoard, ShipManager& enemyShipManager);
    void reset(const GameSettings &gameMode, GameBoard &enemyBoard, ShipManager &enemyShipManager);
    bool isDefeated();
    friend std::ostream& operator<<(std::ostream& os, const UserPlayer& player);
    friend std::istream& operator>>(std::istream& is, UserPlayer& player);
};