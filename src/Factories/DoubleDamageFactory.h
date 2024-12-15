#pragma once

#include "ISkillFactory.h"
#include "../Skills/DoubleDamage.h"
#include "../IO/InputProcessor.h"

class DoubleDamageFactory : public ISkillFactory {
public:
    ISkill* createAbility(GameBoard &enemyBoard, ShipManager &enemyShipManager) override;
};
