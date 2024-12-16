#pragma once

#include "ISkill.h"

class Bombing : public ISkill {
public:
    Bombing(ShipManager& enemyShipManager);
    void apply(size_t ax, size_t ay, GameBoard &enemyBoard, ShipManager &enemyShipManager) override;
    std::string getName() override;
};