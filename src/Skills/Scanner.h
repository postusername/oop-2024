#pragma once

#include "ISkill.h"
#include "../Exceptions/SkillException.h"

class Scanner : public ISkill {
public:
    Scanner(GameBoard& enemyBoard);
    void apply(size_t ax, size_t ay, GameBoard &enemyBoard, ShipManager &enemyShipManager) override;
    std::string getName() override;
};
