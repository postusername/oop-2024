#pragma once

#include "../Skills/ISkill.h"
#include "../GameBoard.h"
#include "../ShipManager.h"

class ISkillFactory {
public:
    virtual ISkill* createAbility(GameBoard &enemyBoard, ShipManager &enemyShipManager) = 0;
    virtual ~ISkillFactory() = default;
};
