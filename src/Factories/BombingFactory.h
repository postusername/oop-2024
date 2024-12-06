#pragma once

#include "ISkillFactory.h"
#include "../Skills/Bombing.h"

class BombingFactory : public ISkillFactory {
public:
    ISkill* createAbility(InputProcessor &inputProcessor, GameBoard &aiBoard, ShipManager &aiShipManager) override;
};