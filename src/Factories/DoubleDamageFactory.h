#pragma once

#include "ISkillFactory.h"
#include "../Skills/DoubleDamage.h"
#include "../IO/InputProcessor.h"

class DoubleDamageFactory : public ISkillFactory {
public:
    ISkill* createAbility(InputProcessor &inputProcessor, GameBoard &enemyBoard, ShipManager &enemyShipManager) override;
};
