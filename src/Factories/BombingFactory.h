#pragma once

#include "ISkillFactory.h"
#include "../Skills/Bombing.h"

class BombingFactory : public ISkillFactory {
public:
    ISkill* createAbility(GameBoard &aiBoard, ShipManager &aiShipManager) override;
};