#pragma once

#include <queue>
#include <vector>
#include "Skills/ISkill.h"
#include "Factories/ISkillFactory.h"
#include "Factories/ScannerFactory.h"
#include "Factories/BombingFactory.h"
#include "Factories/DoubleDamageFactory.h"
#include "Exceptions/SkillException.h"


class SkillManager {
private:
    InputProcessor& inputProcessor;
    GameBoard enemyBoard;
    ShipManager enemyShipManager;
    std::vector<ISkillFactory*> factories;
    std::queue<ISkill*> abilities;

public:
    SkillManager(InputProcessor& inputProcessor, GameBoard& enemyBoard, ShipManager& enemyShipManager);
    ~SkillManager();
    void addSkill();
    void applyAbility();
    void clearAbilities();
    void showAbilities() const;
    friend std::ostream& operator<<(std::ostream& os, SkillManager& manager);
    friend std::istream& operator>>(std::istream& is, SkillManager& manager);
};