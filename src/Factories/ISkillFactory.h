#pragma once

#include "../Skills/ISkill.h"
#include "../IO/InputProcessor.h"

class ISkillFactory {
public:
    virtual ISkill* createAbility(InputProcessor &inputProcessor, GameBoard &enemyBoard, ShipManager &enemyShipManager) = 0;
    virtual ~ISkillFactory() = default;
};
